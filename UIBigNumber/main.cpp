#include "FormBigNumber.h"

using namespace UIBigNumber;

[STAThread]
int main(array<System::String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew FRBigNumber());
    return 0;
}
