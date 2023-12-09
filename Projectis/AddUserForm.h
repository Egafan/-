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
            this->label1->Location = System::Drawing::Point(96, 9);
            this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(166, 16);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Добавить пользователя";
            // 
            // textBox1
            // 
            this->textBox1->Location = System::Drawing::Point(67, 43);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(213, 22);
            this->textBox1->TabIndex = 1;
            this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &AddUserForm::textBox1_KeyPress); // Новая строка
            this->okButton->Enabled = false;
            this->okButton->Location = System::Drawing::Point(125, 81);
            this->okButton->Name = L"okButton";
            this->okButton->Size = System::Drawing::Size(102, 34);
            this->okButton->TabIndex = 2;
            this->okButton->Text = L"OK";
            this->okButton->UseVisualStyleBackColor = true;
            this->okButton->Click += gcnew System::EventHandler(this, &AddUserForm::okButton_Click);
            // 
            // AddUserForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
            this->ClientSize = System::Drawing::Size(379, 137);
            this->Controls->Add(this->okButton);
            this->Controls->Add(this->textBox1);
            this->Controls->Add(this->label1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
            this->Margin = System::Windows::Forms::Padding(4);
            this->MinimizeBox = false;
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

    private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
        // Проверка, содержит ли текст цифры или пуст
        if (System::Text::RegularExpressions::Regex::IsMatch(textBox1->Text, "\\d") || String::IsNullOrWhiteSpace(textBox1->Text)) {
            // Если содержит цифры или пусто, отключаем кнопку OK
            okButton->Enabled = false;
        }
        else {
            // Иначе включаем кнопку OK
            okButton->Enabled = true;
        }
    }

    private: System::Void textBox1_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
        // Проверка, является ли нажатая клавиша буквой или пробелом
        if (!Char::IsLetter(e->KeyChar) && e->KeyChar != 8 && e->KeyChar != ' ') { // 8 - Backspace
            // Если не буква, не пробел и не Backspace, отменить событие
            e->Handled = true;
        }

        // Вызываем метод для проверки текста после нажатия клавиши
        textBox1_TextChanged(sender, e);
    }
    };
}