import sys
import os
import shlex
import subprocess

read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'

if read_the_docs_build:
    subprocess.call('doxygen', shell=True)

extensions = ['breathe']
breathe_projects = { 'Nanoshield_LCD': 'xml' }
breathe_default_project = "Nanoshield_LCD"
templates_path = ['_templates']
source_suffix = '.rst'
master_doc = 'index'
project = u'Nanoshield_LCD'
copyright = u'2015, Nanoshield_LCD'
author = u'Nanoshield_LCD'
version = '1.0'
release = '1.0'
language = None
exclude_patterns = ['_build']
pygments_style = 'sphinx'
todo_include_todos = False
html_static_path = ['_static']
htmlhelp_basename = 'Nanoshield_LCDdoc'
latex_elements = {
}
latex_documents = [
  (master_doc, 'Nanoshield_LCD.tex', u'Nanoshield\_LCD Documentation',
   u'Nanoshield\_LCD', 'manual'),
]
