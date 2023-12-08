#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Data::SqlClient;

[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Projectis::MyForm form;
	Application::Run(% form);
}