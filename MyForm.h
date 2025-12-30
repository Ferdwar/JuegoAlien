#pragma once
#include "Controladora.h"

namespace pc1prueba {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			srand(time(NULL));
			gr = this->CreateGraphics();
			buffer = BufferedGraphicsManager::Current->Allocate(gr, this->ClientRectangle);

			enemigoImg = gcnew Bitmap("Imagenes\\enemigo.jpeg");
			jugadorImg = gcnew Bitmap("Imagenes\\alien1.jpeg");

			control = new Controladora(jugadorImg);
		}

	protected:
		~MyForm()
		{
			if (components) delete components;
			delete control;
		}

	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;

		   Graphics^ gr;
		   BufferedGraphics^ buffer;
		   Bitmap^ jugadorImg;
		   Bitmap^ enemigoImg;
		   Controladora* control;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			   this->SuspendLayout();
			   // 
			   // timer1
			   // 
			   this->timer1->Enabled = true;
			   this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			   // 
			   // MyForm
			   // 
			   this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			   this->ClientSize = System::Drawing::Size(675, 412);
			   this->Name = L"MyForm";
			   this->Text = L"MyForm";
			   this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			   this->ResumeLayout(false);
		   }
#pragma endregion

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		buffer->Graphics->Clear(Color::Black);

		control->generarEnemigoCada3Segundos(enemigoImg->Width / 5, enemigoImg->Height / 5);
		control->moverTodo(buffer->Graphics);
		control->colision(buffer->Graphics);
		control->dibujarTodo(buffer->Graphics, jugadorImg, enemigoImg);

		buffer->Render(gr);
	}

	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode) {
		case Keys::W: control->moverJugador(buffer->Graphics, 'W'); break;
		case Keys::S: control->moverJugador(buffer->Graphics, 'S'); break;
		case Keys::Space: control->disparar(); break;
		}
	}
	};
}
