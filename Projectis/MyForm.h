#pragma once

#include "AddUserForm.h"
#include <string>
#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include <vector>
#include <iostream>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

namespace Projectis {
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Data::SqlClient;
	using namespace System::Collections::Generic;

	public ref class MyForm : public System::Windows::Forms::Form {
	public:
		MyForm(void) {
			InitializeComponent();
			listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::OnConferenceSelected);
			OnConferenceSelected(nullptr, nullptr);
			// Инициализация словаря 
			checkboxStateDictionary = gcnew Dictionary<String^, Dictionary<String^, bool>^>();
			conferenceDictionary = gcnew Dictionary<String^, List<String^>^>();

			String^ connectionString = "Data Source=RIFA\\SQLEXPRESSRIFA;Initial Catalog=Konfirik;Integrated Security=True";

			// Создание подключения
			SqlConnection^ connection = gcnew SqlConnection(connectionString);

			try
			{
				// Открытие подключения
				connection->Open();

				SqlCommand^ cmd = gcnew SqlCommand("SELECT namekonf FROM Konfir", connection);
				SqlDataReader^ rdr = cmd->ExecuteReader();

				// Очистка предыдущих элементов ListBox
				listBox1->Items->Clear();

				// Чтение данных и добавление их в ListBox
				while (rdr->Read())
				{
					String^ data = "";

					// Получение значения столбца по его индексу
					for (int i = 0; i < rdr->FieldCount; i++)
					{
						data += rdr->GetValue(i)->ToString() + "t";
					}

					listBox1->Items->Add(data);
				}

				rdr->Close();
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
			finally
			{
				// Закрытие подключения
				connection->Close();
			}
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
		Dictionary<String^, Dictionary<String^, bool>^>^ checkboxStateDictionary;
		Dictionary<String^, List<String^>^>^ conferenceDictionary;

		void InitializeComponent(void) {
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->listView2 = (gcnew System::Windows::Forms::ListView());
			this->addButton = (gcnew System::Windows::Forms::Button());
			this->deleteButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();

			// Инициализация checkboxStateDictionary
			checkboxStateDictionary = gcnew Dictionary<String^, Dictionary<String^, bool>^>();

			// listBox1
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(12, 44);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(165, 433);
			this->listBox1->TabIndex = 0;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::OnConferenceSelected);

			// label1
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(323, 24);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Учет пользователей для конференций";

			// listView2
			this->listView2->Columns->Add("Дата", 120);
			this->listView2->Columns->Add("Время", 80);
			this->listView2->Columns->Add("Конференция", 200);
			this->listView2->Columns->Add("Пользователь", 300);
			this->listView2->CheckBoxes = true;
			this->listView2->FullRowSelect = true; // Выбирайте всю строку при клике на элемент
			this->listView2->Location = System::Drawing::Point(191, 44);
			this->listView2->Name = L"listView2";
			this->listView2->Size = System::Drawing::Size(684, 433);
			this->listView2->TabIndex = 2;
			this->listView2->View = System::Windows::Forms::View::Details;
			this->listView2->Click += gcnew System::EventHandler(this, &MyForm::listView2_Click);
			// Подписка на событие ItemChecked
			this->listView2->ItemChecked += gcnew ItemCheckedEventHandler(this, &MyForm::OnItemChecked);

			// addButton
			this->addButton->Location = System::Drawing::Point(191, 484);
			this->addButton->Name = L"addButton";
			this->addButton->Size = System::Drawing::Size(75, 23);
			this->addButton->TabIndex = 3;
			this->addButton->Text = L"Добавить";
			this->addButton->UseVisualStyleBackColor = true;
			this->addButton->Click += gcnew
				System::EventHandler(this, &MyForm::addButton_Click);

			// deleteButton
			this->deleteButton->Location = System::Drawing::Point(300, 484);
			this->deleteButton->Name = L"deleteButton";
			this->deleteButton->Size = System::Drawing::Size(75, 23);
			this->deleteButton->TabIndex = 4;
			this->deleteButton->Text = L"Удалить";
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

		void OnItemChecked(System::Object^ sender, ItemCheckedEventArgs^ e) {
			String^ conference = e->Item->SubItems[2]->Text;
			String^ username = e->Item->SubItems[3]->Text;

			if (!checkboxStateDictionary->ContainsKey(conference)) {
				checkboxStateDictionary[conference] = gcnew Dictionary<String^, bool>();
			}

			if (!checkboxStateDictionary[conference]->ContainsKey(username)) {
				checkboxStateDictionary[conference]->Add(username, e->Item->Checked);
			}
		}

		void OnConferenceSelected(System::Object^ sender, System::EventArgs^ e) {
			if (listBox1->SelectedItem != nullptr) {
				String^ selectedConference = listBox1->SelectedItem->ToString();

				// Clear existing items in listView2
				listView2->Items->Clear();

				Dictionary<String^, bool>^ userCheckboxStates = gcnew Dictionary<String^, bool>();
				if (checkboxStateDictionary->ContainsKey(selectedConference)) {
					userCheckboxStates = checkboxStateDictionary[selectedConference];
				}

				// Извлекаем пользователей для выбранной конференции и добавляем их в listView2
				String^ connectionString = "Data Source=RIFA\\SQLEXPRESSRIFA;Initial Catalog=Konfirik;Integrated Security=True";
				SqlConnection^ connection = gcnew SqlConnection(connectionString);

				try {
					connection->Open();

					// Проверим существование конференции в таблице Konfir
					String^ checkConferenceQuery = "SELECT COUNT(*) FROM Konfir WHERE namekonf = @conference";
					SqlCommand^ checkConferenceCmd = gcnew SqlCommand(checkConferenceQuery, connection);
					checkConferenceCmd->Parameters->Add("@conference", System::Data::SqlDbType::VarChar, 255)->Value = selectedConference;
					int conferenceCount = safe_cast<int>(checkConferenceCmd->ExecuteScalar());

					if (conferenceCount == 0) {
						MessageBox::Show("Выбранной конференции не существует в таблице Konfir.");
						return;
					}

					// Продолжение выполнения запроса для Users
					String^ query = "SELECT nameuser FROM Users WHERE conference = @conference";
					SqlCommand^ cmd = gcnew SqlCommand(query, connection);
					cmd->Parameters->Add("@conference", System::Data::SqlDbType::VarChar, 255)->Value = selectedConference;
					SqlDataReader^ rdr = cmd->ExecuteReader();

					// Проверка на наличие данных перед началом цикла чтения
					if (rdr->HasRows) {
						while (rdr->Read()) {
							String^ username = rdr->GetFieldValue<String^>(0);

							// Если есть сохраненное состояние галочки, устанавливаем его
							if (userCheckboxStates->ContainsKey(username)) {
								ListViewItem^ item = gcnew ListViewItem(DateTime::Now.ToString("dd-MM-yyyy"));
								item->SubItems->Add(DateTime::Now.ToString("HH:mm"));
								item->SubItems->Add(selectedConference);
								item->SubItems->Add(username);
								item->Checked = userCheckboxStates[username];

								// Добавляем пользователя в ListView только если его там еще нет
								if (!listView2->Items->Contains(item)) {
									listView2->Items->Add(item);
								}
							}
							else {
								// Если пользователя нет в listView2, то добавляем его
								bool userExists = false;
								for each (ListViewItem ^ item in listView2->Items) {
									if (item->SubItems[3]->Text == username) {
										userExists = true;
										break;
									}
								}

								// Добавляем пользователя в ListView только если его там еще нет
								if (!userExists) {
									ListViewItem^ item = gcnew ListViewItem(DateTime::Now.ToString("dd-MM-yyyy"));
									item->SubItems->Add(DateTime::Now.ToString("HH:mm"));
									item->SubItems->Add(selectedConference);
									item->SubItems->Add(username);
									item->Checked = false;
									listView2->Items->Add(item);
								}
							}
						}
					}
				}
				catch (Exception^ ex) {
					MessageBox::Show("Ошибка при выполнении запроса: " + ex->Message);
				}
				finally {
					if (connection->State == System::Data::ConnectionState::Open) {
						connection->Close();
					}
				}
			}
		}

	private: System::Void addButton_Click(System::Object^ sender, System::EventArgs^ e) {
		AddUserForm^ addUserForm = gcnew AddUserForm();

		if (addUserForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ username = addUserForm->GetUsername();

			if (listBox1->SelectedItem != nullptr) {
				String^ selectedConference = listBox1->SelectedItem->ToString();

				// Добавление пользователя в базу данных
				String^ connectionString = "Data Source=RIFA\\SQLEXPRESSRIFA;Initial Catalog=Konfirik;Integrated Security=True";
				SqlConnection^ connection = gcnew SqlConnection(connectionString);

				try {
					connection->Open();

					// Проверим существование конференции в таблице Konfir
					String^ checkConferenceQuery = "SELECT COUNT(*) FROM Konfir WHERE namekonf = @conference";
					SqlCommand^ checkConferenceCmd = gcnew SqlCommand(checkConferenceQuery, connection);
					checkConferenceCmd->Parameters->Add("@conference", System::Data::SqlDbType::VarChar, 255)->Value = selectedConference;
					int conferenceCount = safe_cast<int>(checkConferenceCmd->ExecuteScalar());

					if (conferenceCount == 0) {
						MessageBox::Show("Выбранной конференции не существует в базе данных.");
						return;
					}

					// Проверяем, не существует ли уже такого пользователя в конференции
					String^ checkUserQuery = "SELECT COUNT(*) FROM Users WHERE nameuser = @username AND conference = @conference";
					SqlCommand^ checkUserCmd = gcnew SqlCommand(checkUserQuery, connection);
					checkUserCmd->Parameters->Add("@username", System::Data::SqlDbType::VarChar, 255)->Value = username;
					checkUserCmd->Parameters->Add("@conference", System::Data::SqlDbType::VarChar, 255)->Value = selectedConference;
					int userCount = safe_cast<int>(checkUserCmd->ExecuteScalar());

					if (userCount > 0) {
						MessageBox::Show("Пользователь " + username + " уже добавлен в конференцию.");
						return;
					}

					// Добавление нового пользователя
					String^ insertUserQuery = "INSERT INTO Users (nameuser, conference) VALUES (@username, @conference)";
					SqlCommand^ insertUserCmd = gcnew SqlCommand(insertUserQuery, connection);
					insertUserCmd->Parameters->Add("@username", System::Data::SqlDbType::VarChar, 255)->Value = username;
					insertUserCmd->Parameters->Add("@conference", System::Data::SqlDbType::VarChar, 255)->Value = selectedConference;
					insertUserCmd->ExecuteNonQuery();
				}
				catch (Exception^ ex) {
					MessageBox::Show("Ошибка при добавлении пользователя в базу данных: " + ex->Message);
				}
				finally {
					if (connection->State == System::Data::ConnectionState::Open) {
						connection->Close();
					}
				}

				// Добавление пользователя в список и обновление ListView
				ListViewItem^ item = gcnew ListViewItem(DateTime::Now.ToString("dd-MM-yyyy"));
				item->SubItems->Add(DateTime::Now.ToString("HH:mm"));
				item->SubItems->Add(selectedConference);
				item->SubItems->Add(username);
				item->Checked = false;
				listView2->Items->Add(item);
			}
		}
	}

	private: System::Void deleteButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (listView2->SelectedItems->Count > 0) {
			// Получаем выделенный элемент
			ListViewItem^ selectedItem = listView2->SelectedItems[0];

			// Получаем информацию о конференции и пользователе
			String^ selectedConference = selectedItem->SubItems[2]->Text;
			String^ username = selectedItem->SubItems[3]->Text;

			// Удаляем пользователя из базы данных
			String^ connectionString = "Data Source=RIFA\\SQLEXPRESSRIFA;Initial Catalog=Konfirik;Integrated Security=True";
			SqlConnection^ connection = gcnew SqlConnection(connectionString);

			try {
				connection->Open();

				// Удаление пользователя из базы данных
				String^ deleteUserQuery = "DELETE FROM Users WHERE nameuser = @username AND conference = @conference";
				SqlCommand^ deleteUserCmd = gcnew SqlCommand(deleteUserQuery, connection);
				deleteUserCmd->Parameters->Add("@username", System::Data::SqlDbType::VarChar, 255)->Value = username;
				deleteUserCmd->Parameters->Add("@conference", System::Data::SqlDbType::VarChar, 255)->Value = selectedConference;
				deleteUserCmd->ExecuteNonQuery();
			}
			catch (Exception^ ex) {
				MessageBox::Show("Ошибка при удалении пользователя из базы данных: " + ex->Message);
			}
			finally {
				if (connection->State == System::Data::ConnectionState::Open) {
					connection->Close();
				}
			}

			// Удаляем пользователя из ListView
			listView2->Items->RemoveAt(selectedItem->Index);

			// Обновление состояния флажков на основе словаря
			if (checkboxStateDictionary->ContainsKey(selectedConference) && checkboxStateDictionary[selectedConference]->ContainsKey(username)) {
				checkboxStateDictionary[selectedConference]->Remove(username);
			}
		}
	}

	private: System::Void listView2_Click(System::Object^ sender, System::EventArgs^ e) {
		if (listView2->SelectedItems->Count > 0) {
			// Возможно, здесь вы захотите выполнить какие-то дополнительные действия при выборе строки
		}
	}
	};
}