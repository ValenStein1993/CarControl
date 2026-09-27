#!/usr/bin/env python3
"""
Generate a C++ header of `inline constexpr` config constants from a YAML file.

Every leaf in the YAML tree becomes one variable named
    config_<key1>_<key2>_..._<keyN>
following the path of keys down to that leaf.

Usage:
    python3 gen_config_hpp.py <input.yaml> <output.hpp>
"""

import sys
from pathlib import Path
import os
import yaml


def cpp_type_and_literal(value):
    """Map a YAML scalar to a (cpp_type, cpp_literal) pair."""
    # bool check must come before int: bool is a subclass of int in Python.
    if isinstance(value, bool):
        return "bool", ("true" if value else "false")
    if isinstance(value, int):
        return "int", str(value)
    if isinstance(value, float):
        return "float", f"{value}f"
    if isinstance(value, str):
        escaped = value.replace("\\", "\\\\").replace('"', '\\"')
        return "std::string_view", f'"{escaped}"'
    raise TypeError(f"Unsupported leaf type {type(value)} for value {value!r}")


def collect_leaves(node, prefix, out):
    """Recursively walk a nested dict, appending (identifier, cpp_type, literal)."""
    if isinstance(node, dict):
        for key, value in node.items():
            collect_leaves(value, prefix + [str(key)], out)
    elif isinstance(node, list):
        path = "_".join(prefix)
        raise TypeError(
            f"Lists aren't supported (at '{path}'). Flatten this key in the yaml, "
            "or extend collect_leaves to emit a std::array."
        )
    else:
        identifier = "config_" + "_".join(prefix)
        cpp_type, literal = cpp_type_and_literal(node)
        out.append((identifier, cpp_type, literal))


def generate_header(yaml_path: Path) -> str:
    with open(yaml_path, "r") as f:
        data = yaml.safe_load(f)

    leaves = []
    collect_leaves(data, [], leaves)

    seen = set()
    for identifier, _, _ in leaves:
        if identifier in seen:
            raise ValueError(f"Name collision: '{identifier}' would be generated twice")
        seen.add(identifier)

    lines = [
        "// AUTO-GENERATED FILE \u2014 do not edit by hand.",
        f"// Generated from yaml by {Path(__file__).name}",
        "#pragma once",
        "",
        "#include <string_view>",
        "",
    ]
    for identifier, cpp_type, literal in leaves:
        lines.append(f"inline constexpr {cpp_type} {identifier} = {literal};")
    lines.append("")
    return "\n".join(lines)


def main():
    if len(sys.argv) != 3:
        print(f"usage: {sys.argv[0]} <config.yaml> <config.hpp>", file=sys.stderr)
        sys.exit(1)

    yaml_path = Path(sys.argv[1]).expanduser()
    out_path = Path(sys.argv[2]).expanduser()

    header = generate_header(yaml_path)
    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_text(header)
    print(f"wrote {out_path}")


if __name__ == "__main__":
    main()
