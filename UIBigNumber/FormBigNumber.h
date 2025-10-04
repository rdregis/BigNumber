#pragma once

#define WIN32_LEAN_AND_MEAN

#define _WINSOCKAPI_    // stops windows.h including winsock.h
#include <winsock2.h>
#include <windows.h>

#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>

#include "BigNumber.h"
#include "BNExecutor.h"
#include "ClientCalculator.h"


namespace UIBigNumber 
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FRBigNumber
	/// </summary>
	public ref class FRBigNumber : public System::Windows::Forms::Form
	{
	public:
		FRBigNumber(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FRBigNumber()
		{
			if (components)
			{
				delete components;
			}
			if (netClient_ != nullptr) {
				delete (netClient_);
			}
		}
	private: System::Windows::Forms::TextBox^ tbFactorY;
	private: System::Windows::Forms::Label^ lbFactorY;
	protected:


	private: System::Windows::Forms::Label^ lbFactorX;

	private: System::Windows::Forms::TextBox^ tbFactorX;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ tbResult;
	private: System::Windows::Forms::ComboBox^ cbOperator;

	private: System::Windows::Forms::Button^ btSubmit;
	private: System::Windows::Forms::TextBox^ tbHost;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ tbPort;
	private: System::Windows::Forms::Button^ btConnect;



	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tbFactorY = (gcnew System::Windows::Forms::TextBox());
			this->lbFactorY = (gcnew System::Windows::Forms::Label());
			this->lbFactorX = (gcnew System::Windows::Forms::Label());
			this->tbFactorX = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tbResult = (gcnew System::Windows::Forms::TextBox());
			this->cbOperator = (gcnew System::Windows::Forms::ComboBox());
			this->btSubmit = (gcnew System::Windows::Forms::Button());
			this->tbHost = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->tbPort = (gcnew System::Windows::Forms::TextBox());
			this->btConnect = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// tbFactorY
			// 
			this->tbFactorY->Location = System::Drawing::Point(7, 169);
			this->tbFactorY->Name = L"tbFactorY";
			this->tbFactorY->Size = System::Drawing::Size(615, 20);
			this->tbFactorY->TabIndex = 0;
			// 
			// lbFactorY
			// 
			this->lbFactorY->AutoSize = true;
			this->lbFactorY->Location = System::Drawing::Point(12, 153);
			this->lbFactorY->Name = L"lbFactorY";
			this->lbFactorY->Size = System::Drawing::Size(47, 13);
			this->lbFactorY->TabIndex = 1;
			this->lbFactorY->Text = L"Factor Y";
			// 
			// lbFactorX
			// 
			this->lbFactorX->AutoSize = true;
			this->lbFactorX->Location = System::Drawing::Point(8, 201);
			this->lbFactorX->Name = L"lbFactorX";
			this->lbFactorX->Size = System::Drawing::Size(47, 13);
			this->lbFactorX->TabIndex = 3;
			this->lbFactorX->Text = L"Factor X";
			// 
			// tbFactorX
			// 
			this->tbFactorX->Location = System::Drawing::Point(7, 220);
			this->tbFactorX->Name = L"tbFactorX";
			this->tbFactorX->Size = System::Drawing::Size(615, 20);
			this->tbFactorX->TabIndex = 2;
			this->tbFactorX->TextChanged += gcnew System::EventHandler(this, &FRBigNumber::textBox2_TextChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(8, 340);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(37, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Result";
			// 
			// tbResult
			// 
			this->tbResult->Location = System::Drawing::Point(7, 359);
			this->tbResult->Name = L"tbResult";
			this->tbResult->Size = System::Drawing::Size(615, 20);
			this->tbResult->TabIndex = 4;
			// 
			// cbOperator
			// 
			this->cbOperator->FormattingEnabled = true;
			this->cbOperator->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"[+] Add", L"[-] Subtract", L"[*] Multiply",
					L"[/] Division", L"[%] Module", L"[\?] Expression"
			});
			this->cbOperator->Location = System::Drawing::Point(12, 113);
			this->cbOperator->Name = L"cbOperator";
			this->cbOperator->Size = System::Drawing::Size(121, 21);
			this->cbOperator->TabIndex = 6;
			this->cbOperator->SelectedValueChanged += gcnew System::EventHandler(this, &FRBigNumber::cbOperator_SelectedValueChanged);
			this->cbOperator->ControlAdded += gcnew System::Windows::Forms::ControlEventHandler(this, &FRBigNumber::cbOperator_ControlAdded);
			// 
			// btSubmit
			// 
			this->btSubmit->Location = System::Drawing::Point(490, 256);
			this->btSubmit->Name = L"btSubmit";
			this->btSubmit->Size = System::Drawing::Size(75, 23);
			this->btSubmit->TabIndex = 7;
			this->btSubmit->Text = L"Submit";
			this->btSubmit->UseVisualStyleBackColor = true;
			this->btSubmit->Click += gcnew System::EventHandler(this, &FRBigNumber::btSubmit_Click);
			// 
			// tbHost
			// 
			this->tbHost->Location = System::Drawing::Point(92, 47);
			this->tbHost->Name = L"tbHost";
			this->tbHost->Size = System::Drawing::Size(100, 20);
			this->tbHost->TabIndex = 8;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 50);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(63, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Server Host";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(259, 50);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(60, 13);
			this->label5->TabIndex = 11;
			this->label5->Text = L"Server Port";
			// 
			// tbPort
			// 
			this->tbPort->Location = System::Drawing::Point(339, 47);
			this->tbPort->Name = L"tbPort";
			this->tbPort->Size = System::Drawing::Size(100, 20);
			this->tbPort->TabIndex = 10;
			this->tbPort->TextChanged += gcnew System::EventHandler(this, &FRBigNumber::textBox2_TextChanged_1);
			// 
			// btConnect
			// 
			this->btConnect->Location = System::Drawing::Point(490, 50);
			this->btConnect->Name = L"btConnect";
			this->btConnect->Size = System::Drawing::Size(75, 23);
			this->btConnect->TabIndex = 12;
			this->btConnect->Text = L"Connect";
			this->btConnect->UseVisualStyleBackColor = true;
			this->btConnect->Click += gcnew System::EventHandler(this, &FRBigNumber::tbConnect_Click);
			// 
			// FRBigNumber
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(726, 420);
			this->Controls->Add(this->btConnect);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->tbPort);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->tbHost);
			this->Controls->Add(this->btSubmit);
			this->Controls->Add(this->cbOperator);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->tbResult);
			this->Controls->Add(this->lbFactorX);
			this->Controls->Add(this->tbFactorX);
			this->Controls->Add(this->lbFactorY);
			this->Controls->Add(this->tbFactorY);
			this->Name = L"FRBigNumber";
			this->Text = L"Big Number Calculator";
			this->Load += gcnew System::EventHandler(this, &FRBigNumber::FRBigNumber_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void cbOperator_ControlAdded(System::Object^ sender, System::Windows::Forms::ControlEventArgs^ e)
	{
		cbOperator->Text = "Add";
	}
	private: System::Void FRBigNumber_Load(System::Object^ sender, System::EventArgs^ e)
	{
		cbOperator->SelectedIndex = 0;
		tbHost->Text = "127.0.0.1";
		tbPort->Text = "11211";
		btSubmit->Enabled = false;

	}
	private: System::Void btSubmit_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		std::string sFactorY(msclr::interop::marshal_as<std::string>(tbFactorY->Text));
		std::string sFactorX(msclr::interop::marshal_as<std::string>(tbFactorX->Text));
		BigNum::MathBigNumber bnFactorY;
		BigNum::MathBigNumber bnFactorX;

		try{
			if (cbOperator->SelectedIndex != 5) {
				BigNum::MathBigNumber bnFactorYY(sFactorY);
				BigNum::MathBigNumber bnFactorXX(sFactorX);
				bnFactorY = bnFactorYY;
				bnFactorX = bnFactorXX;
			}
		}
		catch (const std::exception& ex) {
			std::stringstream ss;
			ss << "BigNumber Error: " << ex.what() << std::endl;
			System::Windows::Forms::MessageBox::Show(msclr::interop::marshal_as<System::String^>(ss.str()));
			return;
		}

		BigNum::MathBigNumber bnRstDiv;

		std::string sOperation;
		switch (cbOperator->SelectedIndex) {
		case 0:
			sOperation = "+";
			break;
		case 1:
			sOperation = "-";
			break;
		case 2:
			sOperation = "*";
			break;
		case 3:
			sOperation = "/";
			break;
		case 4:
			sOperation = "%";
			break;
		case 5:
			sOperation = "%";
			tbFactorX->Text = "";
			tbFactorX->Visible = false;
			break;
		}
		
		std::string sendMessage;
		if (cbOperator->SelectedIndex == 5) {
			sendMessage = sFactorY;
		}
		else{
			sendMessage= sFactorY + sOperation + sFactorX;
		}
		

		try {
			const std::string& bytesReceived = netClient_->sendToServer(sendMessage);
			tbResult->Text = msclr::interop::marshal_as<System::String^>(bytesReceived);
		}
		catch (const std::exception& ex) {
			std::stringstream ss;
			ss << "Client: Error: " << ex.what() << std::endl;
			System::Windows::Forms::MessageBox::Show(msclr::interop::marshal_as<System::String^>(ss.str()));
		}

		
		 


	}

	private: System::Void textBox2_TextChanged_1(System::Object^ sender, System::EventArgs^ e) 
	{
	}
	private: System::Void tbConnect_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		netClient_ = new NET::ClientCalculator();
		
		try {
			netClient_->connectToServer(msclr::interop::marshal_as<std::string>(tbHost->Text), 
				msclr::interop::marshal_as<std::string>(tbPort->Text));
			btConnect->Enabled = false;
			btSubmit->Enabled = true;
		}
		catch (const std::exception& ex) {
			std::stringstream ss;
			ss << "Client: Error: " << ex.what() << std::endl;
			System::Windows::Forms::MessageBox::Show(msclr::interop::marshal_as<System::String^>(ss.str()));
		}

	}
	private:
		NET::ClientCalculator* netClient_ = nullptr;
		private: System::Void cbOperator_SelectedValueChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			if (cbOperator->SelectedIndex == 5) {
				tbFactorX->Text = "";
				tbFactorX->Visible = false;
				lbFactorX->Visible = false;
				lbFactorY->Text = "Expression";
				return;
			}

			lbFactorX->Visible = true;
			tbFactorX->Visible = true;
			lbFactorY->Text = "FactorY";
			
		}
};
}

