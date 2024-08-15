from delphivcl import *
from gen_led import strap
import sys


class MainForm(Form):

    def __init__(self, owner):
        self.Caption = "A VCL Form..."
        self.SetBounds(10, 10, 500, 400)
        self.Position = "poScreenCenter"

        self.lblHello = Label(self)
        self.lblHello.SetProps(Parent=self,
                               Caption="Hello DelphiVCL for Python")
        self.lblHello.SetBounds(10, 10, 300, 24)

        self.OnClose = self.__on_form_close

    def __on_form_close(self, sender, action):
        action.Value = caFree


def main():
    Application.Initialize()
    Application.Title = "Hello Python"
    Main = MainForm(Application)
    Main.Show()
    xx = strap()
    wd = open("east_led.txt", "w")
    rd = open("east_port.txt", "r")
    # rd2 = open("north_led.csv", "r")

    original = sys.stdout
    sys.stdout = open("myout.txt", 'w')
    Main.lblHello.SetProps(Caption="ready to go!!")
    xx.strget(rd, wd)
    sys.stdout = original
    Main.lblHello.SetProps(Caption="file is conducted.")
    rd.close()
    wd.close()

    FreeConsole()
    Application.Run()
    Main.Destroy()


main()
