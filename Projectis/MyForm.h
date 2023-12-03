#pragma once

#include "AddUserForm.h"

namespace Projectis {
    using namespace System;
    using namespace System::Windows::Forms;

    public ref class MyForm : public System::Windows::Forms::Form {
    public:
        MyForm(void) {
            InitializeComponent();

            listBox1->Items->Add("����������� 1");
            listBox1->Items->Add("����������� 2");
            listBox1->Items->Add("����������� 3");

            listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::OnConferenceSelected);
            OnConferenceSelected(nullptr, nullptr);
        }

    protected:
        ~MyForm() {
            if (components) {
                delete components;
            }
        }

    private:
        System::Windows::Forms::ListBox^ listBox1;
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::ListView^ listView2;
        System::Windows::Forms::Button^ addButton;
        System::Windows::Forms::Button^ deleteButton;

        System::ComponentModel::Container^ components;

        void InitializeComponent(void) {
            this->listBox1 = (gcnew System::Windows::Forms::ListBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->listView2 = (gcnew System::Windows::Forms::ListView());
            this->addButton = (gcnew System::Windows::Forms::Button());
            this->deleteButton = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();

            // listBox1
            this->listBox1->FormattingEnabled = true;
            this->listBox1->Location = System::Drawing::Point(12, 44);
            this->listBox1->Name = L"listBox1";
            this->listBox1->Size = System::Drawing::Size(148, 433);
            this->listBox1->TabIndex = 0;

            // label1
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->label1->Location = System::Drawing::Point(13, 13);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(323, 24);
            this->label1->TabIndex = 1;
            this->label1->Text = L"���� ������������� ��� �����������";

            // listView2
            this->listView2->Columns->Add("����", 120);
            this->listView2->Columns->Add("�����", 80);
            this->listView2->Columns->Add("�����������", 200);
            this->listView2->Columns->Add("������������", 300);
            this->listView2->CheckBoxes = true;
            this->listView2->FullRowSelect = true;  // ��������� ��� ������ ��� ����� �� �������
            this->listView2->Location = System::Drawing::Point(191, 44);
            this->listView2->Name = L"listView2";
            this->listView2->Size = System::Drawing::Size(684, 433);
            this->listView2->TabIndex = 2;
            this->listView2->View = System::Windows::Forms::View::Details;
            this->listView2->Click += gcnew System::EventHandler(this, &MyForm::listView2_Click);

            // addButton
            this->addButton->Location = System::Drawing::Point(191, 484);
            this->addButton->Name = L"addButton";
            this->addButton->Size = System::Drawing::Size(75, 23);
            this->addButton->TabIndex = 3;
            this->addButton->Text = L"��������";
            this->addButton->UseVisualStyleBackColor = true;
            this->addButton->Click += gcnew System::EventHandler(this, &MyForm::addButton_Click);

            // deleteButton
            this->deleteButton->Location = System::Drawing::Point(300, 484);
            this->deleteButton->Name = L"deleteButton";
            this->deleteButton->Size = System::Drawing::Size(75, 23);
            this->deleteButton->TabIndex = 4;
            this->deleteButton->Text = L"�������";
            this->deleteButton->UseVisualStyleBackColor = true;
            this->deleteButton->Click += gcnew System::EventHandler(this, &MyForm::deleteButton_Click);

            // MyForm
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(883, 513);
            this->Controls->Add(this->deleteButton);
            this->Controls->Add(this->addButton);
            this->Controls->Add(this->listView2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->listBox1);
            this->Name = L"MyForm";
            this->Text = L"MyForm";
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        void OnConferenceSelected(System::Object^ sender, System::EventArgs^ e) {
            if (listBox1->SelectedItem != nullptr) {
                String^ selectedConference = listBox1->SelectedItem->ToString();
            }
        }

    private: System::Void addButton_Click(System::Object^ sender, System::EventArgs^ e) {
        AddUserForm^ addUserForm = gcnew AddUserForm();

        if (addUserForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            String^ username = addUserForm->GetUsername();

            if (listBox1->SelectedItem != nullptr) {
                ListViewItem^ item = gcnew ListViewItem(DateTime::Now.ToString("dd-MM-yyyy"));
                item->SubItems->Add(DateTime::Now.ToString("HH:mm"));
                item->SubItems->Add(listBox1->SelectedItem->ToString());
                item->SubItems->Add(username);
                item->Checked = false;  // ������������� ������ ���������� � �����������
                listView2->Items->Add(item);
            }
        }
    }

    private: System::Void deleteButton_Click(System::Object^ sender, System::EventArgs^ e) {
        if (listView2->SelectedItems->Count > 0) {
            listView2->Items->RemoveAt(listView2->SelectedItems[0]->Index);
        }
    }

    private: System::Void listView2_Click(System::Object^ sender, System::EventArgs^ e) {
        if (listView2->SelectedItems->Count > 0) {
            // ��������, ����� �� �������� ��������� �����-�� �������������� �������� ��� ������ ������
        }
    }
    };
}