#include "openx.h"
#include "ui_openx.h"
#include <QCompleter>
#include <QLineEdit>
#include <QMessageBox>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

openX::openX(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::openX)
{
    ui->setupUi(this);
    QStringList wordList;
    GetProcessList(wordList);

    lineEdit = new QLineEdit(this);

    QCompleter *completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    lineEdit->setCompleter(completer);

    launchButton = new QPushButton("Launch", this);
    launchButton->setGeometry(200,0,60,25);
    connect(launchButton, SIGNAL(released()), this, SLOT(handleButton()));
}

openX::~openX()
{
    delete ui;
}

void openX::handleButton()
{
    QMessageBox box;
    box.setText("Hello?");
    box.exec();
}

void openX::showError()
{
    QMessageBox box;
    box.setText("Error occured");
    box.exec();
}

bool openX::GetProcessList(QStringList &wordList)
{
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if( hProcessSnap == INVALID_HANDLE_VALUE )
    {
        showError();
        return false;
    }

    // Set the size of the structure before using it.
    pe32.dwSize = sizeof( PROCESSENTRY32 );

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if( !Process32First( hProcessSnap, &pe32 ) )
    {
        showError();
        CloseHandle( hProcessSnap );          // clean the snapshot object
        return( true );
    }

    // Now walk the snapshot of processes, and
    // display information about each process in turn
    do
    {
        _tprintf( TEXT("\n\n=====================================================" ));
        _tprintf( TEXT("\nPROCESS NAME:  %s"), pe32.szExeFile );
        _tprintf( TEXT("\n-------------------------------------------------------" ));

        char ch[260];
        char DefChar = ' ';
        WideCharToMultiByte(CP_ACP,0, pe32.szExeFile,-1, ch,260,&DefChar, NULL);

        //A std:string  using the char* constructor.
        QString ss(ch);

        // Retrieve the priority class.
        dwPriorityClass = 0;
        hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID );
        SetForegroundWindow(hProcess.MainWindowHandle);
        if( hProcess == NULL )
            printError( TEXT("OpenProcess") );
        else
        {
            dwPriorityClass = GetPriorityClass( hProcess );
            if( !dwPriorityClass )
                printError( TEXT("GetPriorityClass") );
            CloseHandle( hProcess );
        }

        _tprintf( TEXT("\n  Process ID        = 0x%08X"), pe32.th32ProcessID );
        _tprintf( TEXT("\n  Thread count      = %d"),   pe32.cntThreads );
        _tprintf( TEXT("\n  Parent process ID = 0x%08X"), pe32.th32ParentProcessID );
        _tprintf( TEXT("\n  Priority base     = %d"), pe32.pcPriClassBase );
        if( dwPriorityClass )
            _tprintf( TEXT("\n  Priority class    = %d"), dwPriorityClass );


    } while( Process32Next( hProcessSnap, &pe32 ) );

    CloseHandle( hProcessSnap );
    return( TRUE );
}





