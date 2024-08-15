program PythonFrm;

uses
  Vcl.Forms,
  python_code_run in 'python_code_run.pas' {Form6};

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TForm6, Form6);
  Application.Run;
end.
