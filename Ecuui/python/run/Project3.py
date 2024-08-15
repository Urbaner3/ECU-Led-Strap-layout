from delphivcl import *
from python_code_run import Form6

def main():
    Application.Initialize()
    Application.Title = 'Demo of python'
    MainForm = Form6(Application)
    MainForm.Show()
    FreeConsole()
    Application.Run()

if __name__ == '__main__':
    main()
