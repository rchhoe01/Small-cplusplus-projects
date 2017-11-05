#pragma once
#using<system.dll>  
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
//using namespace System::Data;
using namespace System::Drawing;
using namespace System::Security::Permissions;
using namespace System::IO;

namespace CppWinForm1 {

	

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm sealed : public Form, public IMessageFilter
	{
	private:
		static const int WM_KEYDOWN = 0x100;
	public:
		MyForm(void)
		{
			InitializeComponent();

		}
		[SecurityPermission(SecurityAction::LinkDemand,
			Flags = SecurityPermissionFlag::UnmanagedCode)]
		virtual bool PreFilterMessage(Message% m)
		{
			// Detect key down messages.
			if (m.Msg == WM_KEYDOWN)
			{
				Keys keyCode = (Keys)((int)m.WParam) & Keys::KeyCode;
				// Determine whether the keystroke is a number from the top of
				// the keyboard, or a number from the keypad.
				if (((keyCode >= Keys::D0) && (keyCode <= Keys::D9))
					|| ((keyCode >= Keys::NumPad0)
						&& (keyCode <= Keys::NumPad9)))
				{
					MessageBox::Show(
						"IMessageFilter.PreFilterMessage: '" +
						keyCode.ToString() + "' pressed.");

					if ((keyCode == Keys::D0) || (keyCode == Keys::NumPad0))
					{
						MessageBox::Show(
							"IMessageFilter.PreFilterMessage: '" +
							keyCode.ToString() + "' consumed.");
						return true;
					}
				}
			}

			// Forward all other messages.
			return false;
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::Label^  label1;




	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;





#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->Enabled = false;
			this->richTextBox1->Location = System::Drawing::Point(12, 456);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(578, 96);
			this->richTextBox1->TabIndex = 1;
			this->richTextBox1->Text = L"";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::ControlLight;
			this->label1->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(705, 528);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(54, 24);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Reset";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(771, 564);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->richTextBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::MyForm_KeyPress);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		int row = 1000;
		int col = 1000;
		int startRow;
		int startCol;
		int goalRow;
		int goalCol;
		
		int pointRow;
		int pointCol;
		int pointValue;
		//List<List<int>^>^ matrix = gcnew List<List<int>^>();
		cli::array<int, 2> ^matrix = gcnew array<int, 2>(row,col);
		List<int>^ matrixTemp = gcnew List<int>();
		cli::array<Label ^, 2> ^bInt = gcnew array<Label ^, 2>(row, col);

	/*public: int^ matrixValue(int row, int col) {
		matrixTemp->Clear();
		matrixTemp = matrix[row];
		return matrixTemp[col];
	}*/
		
	public: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		
		this->richTextBox1->Text = richTextBox1->Text;

		String^ fileName = "maze.txt";
		try
		{
			String^ delimStr = " ,.:\t";
			this->richTextBox1->Text = richTextBox1->Text + L"trying to open file " + fileName + L"...\r\n";
			StreamReader^ din = File::OpenText(fileName);
			array<Char>^ delimiter = delimStr->ToCharArray();
			array<String^>^ words;
			String^ str;
			str = din->ReadLine();
			words = str->Split(delimiter);
			int count = 0;
			
			row = System::Convert::ToInt32(words[0]);
			col = System::Convert::ToInt32(words[1]);
			startRow = System::Convert::ToInt32(words[2]);
			startCol = System::Convert::ToInt32(words[3]);
			goalRow = System::Convert::ToInt32(words[4]);
			goalCol = System::Convert::ToInt32(words[5]);
			//read matrix from file and fill m x n list
			int b = 0;
			while ((str = din->ReadLine()) != nullptr)
			{
				words->Clear;
				words = str->Split(delimiter);
				/*matrix->Add(gcnew List<int>());
				for (int a = 0; a < col; a++) {
					matrix[b]->Add(System::Convert::ToInt32(words[a]));
				}*/
				for (int a = 0;a < col; a++) {
					matrix[b, a] = (System::Convert::ToInt32(words[a]));
				}
				b++;
			}
			//fill form with labels
			//populate bInt array
			int pos = 3;
			int posY = 3;
			int^ labelnum = 0;
			//creates the labels on screen and fill labels using matrix read from file
			//for each(array<Label^, 1>^ b in bInt)
			for(int r = 0; r<row;r++ )
			{
				//matrixTemp = matrix[matrixCount];
				for (int c = 0; c < col; c++) {
					bInt[r,c] = gcnew System::Windows::Forms::Label();
					this->Controls->Add(bInt[r,c]);
					bInt[r,c]->BackColor = System::Drawing::Color::White;
					bInt[r,c]->Size = System::Drawing::Size(45, 45);
					bInt[r,c]->Location = System::Drawing::Point(pos, posY);
					labelnum = matrix[r, c];
					bInt[r,c]->Text = bInt[r,c]->Text + labelnum;
					bInt[r,c]->TextAlign = ContentAlignment::MiddleCenter;
					bInt[r, c]->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13));
					pos = pos + 50;
					this->richTextBox1->Text = richTextBox1->Text + matrix[r,c] + " ";
				}
				this->richTextBox1->Text = richTextBox1->Text + "\r\n";
				pos = 3;
				posY = posY + 50;
			}
			pointRow = startRow;
			pointCol = startCol;
		
			bInt[startRow,startCol]->BackColor = System::Drawing::Color::Red;
			bInt[goalRow,goalCol]->BackColor = System::Drawing::Color::Green;
		}
		catch (Exception^ e)
		{
			if (dynamic_cast<FileNotFoundException^>(e))
				this->richTextBox1->Text = richTextBox1->Text + L"file " + fileName + L" not found\r\n";
			//Console::WriteLine("file '{0}' not found", fileName);
			else
				this->richTextBox1->Text = richTextBox1->Text + L"problem reading file " + fileName + L"\r\n";
			//Console::WriteLine("problem reading file '{0}'", fileName);
		}
	}
	

	private: System::Void MyForm_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		// press up or w
		if (e->KeyChar == 'w')
            {
               /* MessageBox::Show("Form.KeyPress: '" +
                    e->KeyChar.ToString() + "' pressed.");
				MessageBox::Show("Control.KeyPress: '" +
					e->KeyChar.ToString() + "' consumed.");*/
			if ((pointRow - pointValue) >= 0) {
				bInt[pointRow, pointCol]->BackColor = System::Drawing::Color::White;
				pointRow = pointRow - pointValue;
				pointValue = matrix[pointRow, pointCol];
				bInt[pointRow, pointCol]->BackColor = System::Drawing::Color::Red;
			}
			else {
				MessageBox::Show("Illegal move: cannot move up");
			}
				e->Handled = true;
            }
		// press down or s
		if (e->KeyChar == 's')
		{
			/*MessageBox::Show("Form.KeyPress: '" +
				e->KeyChar.ToString() + "' pressed.");
			MessageBox::Show("Control.KeyPress: '" +
				e->KeyChar.ToString() + "' consumed.");*/
			if ((pointRow + pointValue) < row) {
				bInt[pointRow, pointCol]->BackColor = System::Drawing::Color::White;
				pointRow = pointRow + pointValue;
				pointValue = matrix[pointRow, pointCol];
				bInt[pointRow, pointCol]->BackColor = System::Drawing::Color::Red;
			}
			else {
				MessageBox::Show("Illegal move: cannot move down");
			}
			e->Handled = true;
		}
		// press left or a
		if (e->KeyChar == 'a')
		{
			/*MessageBox::Show("Form.KeyPress: '" +
				e->KeyChar.ToString() + "' pressed.");
			MessageBox::Show("Control.KeyPress: '" +
				e->KeyChar.ToString() + "' consumed.");*/
			if ((pointCol - pointValue) >= 0) {
				bInt[pointRow, pointCol]->BackColor = System::Drawing::Color::White;
				pointCol = pointCol - pointValue;
				pointValue = matrix[pointRow, pointCol];
				bInt[pointRow, pointCol]->BackColor = System::Drawing::Color::Red;
			}
			else {
				MessageBox::Show("Illegal move: cannot move left");
			}
			e->Handled = true;
		}
		// press right or d
		if (e->KeyChar == 'd')
		{
			/*MessageBox::Show("Form.KeyPress: '" +
				e->KeyChar.ToString() + "' pressed.");
			MessageBox::Show("Control.KeyPress: '" +
				e->KeyChar.ToString() + "' consumed.");*/
			if ((pointCol + pointValue) < col) {
				bInt[pointRow, pointCol]->BackColor = System::Drawing::Color::White;
				pointCol = pointCol + pointValue;
				pointValue = matrix[pointRow, pointCol];
				bInt[pointRow, pointCol]->BackColor = System::Drawing::Color::Red;
			}
			else {
				MessageBox::Show("Illegal move: cannot move right");
			}
			e->Handled = true;
		}
	}
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	bInt[pointRow, pointCol]->BackColor = System::Drawing::Color::White;
	pointCol = startCol;
	pointRow = startRow;
	pointValue = matrix[pointRow, pointCol];
	bInt[pointRow, pointCol]->BackColor = System::Drawing::Color::Red;
	bInt[goalRow, goalCol]->BackColor = System::Drawing::Color::Green;
}
};
}
[STAThread]
int main()
{
	Application::EnableVisualStyles();
	Application::Run(gcnew CppWinForm1::MyForm());
}
