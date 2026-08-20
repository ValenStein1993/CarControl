import os
import yaml
from ament_index_python.packages import get_package_share_directory
from jinja2 import Environment, FileSystemLoader

config_abs = os.path.join(get_package_share_directory('common'), 'config', 'config.yaml')
with open(config_abs, 'r') as f:
    config = yaml.safe_load(f)


env = Environment(loader=FileSystemLoader("./"))
template = env.get_template("template_carmodel.sdf.jinja")
sdf = template.render(**config)

with open("./carmodel.sdf", "w") as f:
    f.write(sdf)




