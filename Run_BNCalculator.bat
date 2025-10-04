@echo off
cls


echo **********************************************************
echo *
echo * Big Number Calculator
echo *
echo **********************************************************
echo.

set host=127.0.0.1
set port=11211
set BNInputFile=DataCalculator.txt
set BNOutputFile=DataCalculatorOut.txt
set BUILDER="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe"

set BNServer=.\x64\Release\BNCalculatorServer.exe
set BNClient=.\x64\Release\BNCalculatorClient.exe
set BNUnityTest=.\x64\Release\TestBigNumber.exe

if not exist %BNServer% (
	call::compileSolution x64 Release BigNumCalculator
)


call::runUnityTest %BNUnityTest%

del /Q /F %BNOutputFile%

echo Running Server and Client ...
echo.
@start /b cmd /c %BNServer% 0.0.0.0 %port% > DataServer.log
%BNClient% %host% %port% %BNInputFile% %BNOutputFile% > DataClient.log


echo **********************************************************
echo *
echo * Resultado da execucao do calculo Big Number
echo * Operacoes suportadas (com prioridade matematica)
echo * [+] Adicao
echo * [-] Subtracao
echo * [*] Multiplicacao
echo * [/] Divisao
echo * [%%] Divisao Modular (Resto)
echo *
echo **********************************************************
echo.

type %BNOutputFile%

goto:eof


# Functions


:runUnityTest 
::--------------
set unityTest=%~1

echo Running unity tests ...
echo.

%unityTest%
if %errorlevel% neq 0 (
	call::endError 1 "Unity Test %unityTest%!"
)

goto:eof

:compileSolution 
::--------------
set vsplataf=%~1
set vsconfig=%~2
set solution=%~3


echo "-----------------------------------------------------------------------"
echo "-----------------------------------------------------------------------"

echo.
echo "Begin %vsconfig% build solution %solution%"

@echo on
%BUILDER% %solution%.sln /p:VisualStudioVersion=%VSVersion%.0 /p:Platform=%vsplataf% /p:Configuration=%vsconfig% /m
@echo off

if %errorlevel% neq 0 (
	call::endError 1 "Build solution %solution%!"
)

goto:eof

:endError 
::--------- 
set testExit=%~1
set message=%~2

echo.
echo "***********************************************************************"
echo "***********************************************************************"
echo "***********************************************************************"
echo "*"
echo "* 	Fatal Error: "
echo "*          %message% "
echo "*"
echo "***********************************************************************"
echo "***********************************************************************"
echo "***********************************************************************"
echo.
 
if %testExit% == 1 (
	echo Atencao: Apos o enter, o prompt CMD sera fechado (interrompa com ctrl C)
	pause
)