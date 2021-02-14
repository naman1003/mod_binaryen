import os

config.binaryen_src_root = r'/home/naman/binaryen1/binaryen'
config.binaryen_build_root = r'/home/naman/binaryen1/binaryen'

lit_config.load_config(
    config, os.path.join(config.binaryen_src_root, 'test', 'lit', 'lit.cfg.py'))
