import os
from delphivcl import *

class Form6(Form):

    def __init__(self, owner):
        self.Memo1 = None
        self.Memo2 = None
        self.Panel1 = None
        self.Button1 = None
        self.Button2 = None
        self.Button3 = None
        self.OpenDialog1 = None
        self.SaveDialog1 = None
        self.LoadProps(os.path.join(os.path.dirname(os.path.abspath(__file__)), "python_code_run.pydfm"))

    def Button1Click(self, Sender):
        pass

    def Button2Click(self, Sender):
        pass

    def Button3Click(self, Sender):
        pass