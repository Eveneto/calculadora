; Calculadora Qt C++ - Script Instalador NSIS
; Cria um instalador Windows profissional

!include "MUI2.nsh"

; Informações do aplicativo
Name "Calculadora Qt C++"
OutFile "calculadora-setup.exe"
InstallDir "$PROGRAMFILES\Calculadora Qt"
InstallDirRegKey HKCU "Software\CalculadoraQt" ""
RequestExecutionLevel admin

; Variáveis
Var StartMenuFolder

; Interface moderna
!define MUI_ABORTWARNING
!define MUI_ICON "icon.ico"
!define MUI_UNICON "icon.ico"

; Páginas do instalador
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "LICENSE.txt"
!insertmacro MUI_PAGE_DIRECTORY

!define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\CalculadoraQt"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
!insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder

!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

; Páginas do desinstalador
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

; Idiomas
!insertmacro MUI_LANGUAGE "PortugueseBR"

; Seção de instalação
Section "Calculadora" SecCalculadora

    SetOutPath "$INSTDIR"
    
    ; Arquivos principais
    File "dist\calculadora.exe"
    File /r "dist\*.*"
    
    ; Criar README
    FileOpen $0 "$INSTDIR\README.txt" w
    FileWrite $0 "🧮 Calculadora Qt C++ v1.0.0$\r$\n"
    FileWrite $0 "$\r$\n"
    FileWrite $0 "✨ Funcionalidades:$\r$\n"
    FileWrite $0 "- Interface gráfica moderna$\r$\n"
    FileWrite $0 "- Operações matemáticas básicas (+, -, ×, ÷)$\r$\n"
    FileWrite $0 "- Histórico de operações$\r$\n"
    FileWrite $0 "- Suporte completo a teclado$\r$\n"
    FileWrite $0 "- Formatação brasileira de números$\r$\n"
    FileWrite $0 "$\r$\n"
    FileWrite $0 "🚀 Para executar: calculadora.exe$\r$\n"
    FileWrite $0 "$\r$\n"
    FileWrite $0 "📧 Repositório: https://github.com/Eveneto/calculadora$\r$\n"
    FileClose $0
    
    ; Registro do Windows
    WriteRegStr HKCU "Software\CalculadoraQt" "" $INSTDIR
    
    ; Desinstalador
    WriteUninstaller "$INSTDIR\Uninstall.exe"
    
    ; Entradas do Menu Iniciar
    !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
        CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
        CreateShortcut "$SMPROGRAMS\$StartMenuFolder\Calculadora Qt.lnk" "$INSTDIR\calculadora.exe"
        CreateShortcut "$SMPROGRAMS\$StartMenuFolder\Desinstalar.lnk" "$INSTDIR\Uninstall.exe"
    !insertmacro MUI_STARTMENU_WRITE_END
    
    ; Atalho na área de trabalho
    CreateShortcut "$DESKTOP\Calculadora Qt.lnk" "$INSTDIR\calculadora.exe"
    
    ; Adicionar/Remover Programas
    WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\CalculadoraQt" "DisplayName" "Calculadora Qt C++"
    WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\CalculadoraQt" "UninstallString" "$INSTDIR\Uninstall.exe"
    WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\CalculadoraQt" "DisplayIcon" "$INSTDIR\calculadora.exe"
    WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\CalculadoraQt" "Publisher" "Eveneto"
    WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\CalculadoraQt" "DisplayVersion" "1.0.0"
    WriteRegDWORD HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\CalculadoraQt" "NoModify" 1
    WriteRegDWORD HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\CalculadoraQt" "NoRepair" 1

SectionEnd

; Seção de desinstalação
Section "Uninstall"

    ; Remover arquivos
    Delete "$INSTDIR\calculadora.exe"
    Delete "$INSTDIR\README.txt"
    Delete "$INSTDIR\Uninstall.exe"
    RMDir /r "$INSTDIR"
    
    ; Remover atalhos
    !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder
    Delete "$SMPROGRAMS\$StartMenuFolder\Calculadora Qt.lnk"
    Delete "$SMPROGRAMS\$StartMenuFolder\Desinstalar.lnk"
    RMDir "$SMPROGRAMS\$StartMenuFolder"
    Delete "$DESKTOP\Calculadora Qt.lnk"
    
    ; Remover registros
    DeleteRegKey HKCU "Software\CalculadoraQt"
    DeleteRegKey HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\CalculadoraQt"

SectionEnd
