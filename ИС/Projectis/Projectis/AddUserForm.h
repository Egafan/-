#pragma once

namespace Projectis {

    using namespace System;
    using namespace System::Windows::Forms;

    public ref class AddUserForm : public System::Windows::Forms::Form
    {
    public:
        AddUserForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~AddUserForm()
        {
            // Нет необходимости удалять components здесь
            // компоненты автоматически удаляются при закрытии формы
        }

    private:
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::TextBox^ textBox1;
        System::Windows::Forms::Button^ okButton;

        void InitializeComponent(void)
        {
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->okButton = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(12, 12);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(131, 13);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Добавить пользователя";
            // 
            // textBox1
            // 
            this->textBox1->Location = System::Drawing::Point(12, 28);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(131, 20);
            this->textBox1->TabIndex = 1;
            // 
            // okButton
            // 
            this->okButton->Location = System::Drawing::Point(12, 54);
            this->okButton->Name = L"okButton";
            this->okButton->Size = System::Drawing::Size(75, 23);
            this->okButton->TabIndex = 2;
            this->okButton->Text = L"OK";
            this->okButton->UseVisualStyleBackColor = true;
            this->okButton->Click += gcnew System::EventHandler(this, &AddUserForm::okButton_Click);
            // 
            // AddUserForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(284, 111);
            this->Controls->Add(this->okButton);
            this->Controls->Add(this->textBox1);
            this->Controls->Add(this->label1);
            this->Name = L"AddUserForm";
            this->Text = L"AddUserForm";
            this->ResumeLayout(false);
            this->PerformLayout();

        }

    public:
        String^ GetUsername()
        {
            return textBox1->Text;
        }

    private:
        System::Void okButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        }
    };
}
