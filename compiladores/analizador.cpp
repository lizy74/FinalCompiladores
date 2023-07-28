/* CODIGO FUENTE FUNCIONAL LEXICO, SINTACTICO Y SEMANTICO/
/* EJEMPLOS DEL LENGUAJE TRADUCTOR *
traductor(){
suma(10 + 30);
resta (20 + 30);
multiplicacion(10 * 20 *30);
division (10 * 30);
}

traductor(){
num1=25;
num2=35;
num3=45;

suma(14,15,num1);
resta(20,15,num3);
multiplicacion(40,num2);
division(20,num1);
}

* PALABRAS CLAVE Y SIGNOS QUE CORRESPONDEN AL LENGUAJE **
TRADUCTOR
(
)
{
}
=
;
,
+
-
*
/
suma
resta
multiplicacion
division

VAR
NUM


* LISTA DE SENTENCIAS *****
ASIGNACIONES
OPERACION SUMA
OPERACION RESTA
OPERACION MULTIPLICACION
OPERACION DIVISION

* DIBUJAR EL AUTOMATA *****


* ERRORES SEMANTICOS ******
LAS VARIABLES NO ESTAN REGISTRADAS EN LA TABLA DE SIMBOLOS
LAS VARIABLES NO TIENEN UN VALOR ASIGNADO

********/

#include <iostream>
#include <string.h>
#include <list>
#include <vector>
#include <sstream>

#define TRADUCTOR    0
#define APAR        1
#define CPAR        2
#define ALLAVE      3
#define CLLAVE      4
#define IGUAL       5
#define PCOMA       6
#define COMA        7
#define SUMA        8
#define RESTA       9
#define MULTIPLICACION  10
#define DIVISION       11
#define VAR        12
#define NUM         13
#define COUT        14
#define CIN        15
#define IDENTIFICADOR 16
#define MAS 17
#define MENOS 18
#define POR 19



#define FIN     666
#define ERROR   999

#define null "6c3e226b4d4795d518ab341b0824ec29"
#define vacio "-"
#define asignado "asignado"

using namespace std;

class Atributos{
public:
	string lexema;
	int token;
	string tipo;
	string valor;
	string estado;
	Atributos(){
		lexema="";
		token=-999;
		tipo="";
		valor=null;
		estado="";
	}
		Atributos(string lex,int tok,string tip,string val,string est){
			lexema=lex;
			token=tok;
			tipo=tip;
			valor=val;
			estado=est;
		}
			
			void Mostrar(){
				cout<<"Tipo("<<tipo<<") \t";
				cout<<"Lexema("<<lexema<<") \t";
				cout<<"Token("<<token<<") \t";
				cout<<"Valor("<<valor<<") \t";
				cout<<"Estado("<<estado<<")"<<endl;
			}
};

class TablaSimbolos{
private:
	list<Atributos> tabla;
public:
	void Insertar(string lex,int tok,string tip,string val,string est){
		Atributos attr(lex,tok,tip,val,est);
		tabla.push_back(attr);
	}
		bool ActualizarValor(string lex,string val){
			for (auto &item:tabla){
				if(item.lexema == lex){
					item.valor = val;
					return true;
				}
			}
			return false;
		}
			bool ActualizarEstado(string lex,string est){
				for (auto &item:tabla){
					if(item.lexema == lex){
						item.estado = est;
						return true;
					}
				}
				return false;
			}
				void Mostrar(){
					for (auto item:tabla){
						item.Mostrar();
					}
				}
					bool Buscar(string lex,Atributos&attr){
						for (auto item:tabla){
							if(item.lexema == lex){
								attr=item;
								return true;
							}
						}
						return false;
					}
						bool BuscarPClave(string lex,Atributos&attr){
							for (auto item:tabla){
								if(item.lexema == lex && item.tipo == "pclave"){
									attr=item;
									return true;
								}
							}
							return false;
						}
							list<Atributos> getTabla(){
								return tabla;
							}
};

class Analisis{
private:
	int i;
	char cad[1000];
	int estado;
	string numero;
	string variable;
	//22 SON LOS ESTADOS DEL AUTOMATA
	//15 SON LOS ELEMENTOS QUE PERTENECEN AL LENGUAJE
	int tTransicion[22][15];
	TablaSimbolos ts;
public:
	Analisis(char input[100]){
		//Aquí hacer la apertura de archivo de texto plano
		strcpy(cad,input);
		i=0;
		
		ts.Insertar("traductor",TRADUCTOR,"pclave",vacio,vacio);
		ts.Insertar("(",APAR,"pclave",vacio,vacio);
		ts.Insertar(")",CPAR,"pclave",vacio,vacio);
		ts.Insertar("{",ALLAVE,"pclave",vacio,vacio);
		ts.Insertar("}",CLLAVE,"pclave",vacio,vacio);
		ts.Insertar("=",IGUAL,"pclave",vacio,vacio);
		ts.Insertar(";",PCOMA,"pclave",vacio,vacio);
		ts.Insertar(",",COMA,"pclave",vacio,vacio);
		ts.Insertar("suma",SUMA,"pclave",vacio,vacio);
		ts.Insertar("resta",RESTA,"pclave",vacio,vacio);
		ts.Insertar("multiplicacion",MULTIPLICACION,"pclave",vacio,vacio);
		ts.Insertar("division",DIVISION,"pclave",vacio,vacio);
		
		for(int ii=0;ii<22;ii++){
			for(int jj=0;jj<15;jj++){
				tTransicion[ii][jj]=ERROR;
			}
		}
		
		tTransicion[0][TRADUCTOR]=1;
		tTransicion[1][APAR]=2;
		tTransicion[2][CPAR]=3;
		tTransicion[3][ALLAVE]=4;
		tTransicion[4][VAR]=5;
		
		tTransicion[4][SUMA]=8;
		tTransicion[4][RESTA]=8;
		tTransicion[4][MULTIPLICACION]=16;
		tTransicion[4][DIVISION]=16;
		//  tTransicion[4][CLLAVE]=21;
		
		tTransicion[5][IGUAL]=6;
		tTransicion[8][APAR]=9;
		tTransicion[16][APAR]=17;
		
		tTransicion[6][VAR]=7;
		tTransicion[6][NUM]=7;
		
		
		
		tTransicion[9][VAR]=10;
		tTransicion[9][NUM]=10;
		tTransicion[17][VAR]=18;
		tTransicion[17][NUM]=18;
		
		
		
		tTransicion[10][COMA]=11;
		tTransicion[18][COMA]=19;
		
		tTransicion[19][VAR]=20;
		tTransicion[19][NUM]=20;
		
		tTransicion[20][COMA]=11;
		// tTransicion[10][COMA]=11;
		
		tTransicion[11][VAR]=12;
		tTransicion[11][NUM]=12;
		
		tTransicion[12][COMA]=13;
		
		tTransicion[13][VAR]=14;
		tTransicion[13][NUM]=14;
		tTransicion[14][CPAR]=15;
		tTransicion[15][PCOMA]=4;
		tTransicion[7][PCOMA]=4;
		tTransicion[4][CLLAVE]=21;
	}
	bool iselement(char c){
		char elements[100];
		/*AQUI DEBEN DE DEFINIR LOS CARACTERES QUE NO SEAN LETRAS O NUMEROS Y QUE CORRESPONDAN AL LENGUAJE*/
		/*NO DEBEN DE REPETIR CARACTERES*/
		strcpy(elements,"(){}=,;");/*<- AQUI*/
		int elements_cont=0;
		while(elements[elements_cont]!='\0'){
			if(elements[elements_cont]==c)
				return true;
			elements_cont++;
		}
		return false;
	}
		
		int getToken(){
			while(cad[i]==' '){
				i++;
			}
			if(cad[i]=='\0'){
				return FIN;
			}
			/*AQUI PUEDE QUE SE TRATE DE UNA VARIABLE O UNA PALABRA CLAVE*/
			else if(isalpha(cad[i])){
				string tmp;
				while(isalpha(cad[i]) || isdigit(cad[i])){
					tmp += cad[i];
					i++;
				}
				Atributos attr;
				string lex = tmp;
				// Buscar en la tabla de símbolos
				for (auto item : ts.getTabla()) {
					if (ts.BuscarPClave(lex, attr)) {
						return attr.token;
					}
				}
				variable = tmp;
				return VAR;
			}
			else if(isdigit(cad[i])){
				string tmp;
				while(isdigit(cad[i])){
					tmp += cad[i];
					i++;
				}
				numero = tmp;
				return NUM;
			}
			else if(iselement(cad[i])){
				if(iselement(cad[i+1])){
					string tmp;
					tmp += cad[i];
					tmp += cad[i+1];
					Atributos attr;
					string lex = tmp;
					for (auto item : ts.getTabla()) {
						if (ts.BuscarPClave(lex, attr)) {
							i++;
							i++;
							return attr.token;
						}
					}
				}
				string tmp;
				tmp += cad[i];
				Atributos attr;
				string lex = tmp;
				for (auto item : ts.getTabla()) {
					if (ts.BuscarPClave(lex, attr)) {
						i++;
						return attr.token;
					}
				}
				i++;
				return ERROR;
			}
			else{
				i++;
				return ERROR;
			}
		}
			
			bool Lexico() {
				int token = 0;
				while (true) {
					token = getToken();
					cout << "Lexico: " << token << endl;
					if (token == FIN) {
						ts.Mostrar();
						return true;
					} else if (token == VAR) {
						Atributos attr;
						if (!ts.Buscar(variable, attr)) {
							ts.Insertar(variable, VAR, "var", null, null);
						}
					} else if (token == ERROR) {
						// Aquí debes mostrar el error de la manera más específica posible
						Error(100);
						return false;
					}
				}
			}
			
			
			bool Sintactico() {
				i = 0;
				int token = 0;
				estado = 0; /*ASIGNAR EL ESTADO INICIAL*/
				while (true) {
					token = getToken();
					cout << estado << " " << token << endl;
					if (token == FIN) {
						if (estado == 21) /*VERIFICAR EL ESTADO FINAL*/
							return true;
						Error(2000);
						return false;
					}
					cout<<"(e"<<estado<<",t"<<token<<")"<<endl;
					estado = tTransicion[estado][token];
					if (estado == ERROR) {
						Error(400);
						return false;
					}
				}
				return false;
			}
			
			bool Semantico(){
				i=0;
				int token=0;
				while(true){
					token=getToken();
					if(token==FIN){
						ts.Mostrar();
						return true;
					}
					if(token==SUMA || token==RESTA){
						//cuadrado(posx,100,lado);
						token=getToken();
						Atributos attr;
						for(int ii=0;ii<3;ii++){
							token=getToken();
							if(token==VAR){
								if(!ts.Buscar(variable,attr)){
									Error(1500);
									return false;
								}
								else if(attr.estado == null){
									Error(1600);
									return false;
								}
							}
							token=getToken();
						}
						token=getToken();
					}
					else if(token==MULTIPLICACION || token==DIVISION){
						token=getToken();
						Atributos attr;
						for(int ii=0;ii<4;ii++){
							token=getToken();
							if(token==VAR){
								if(!ts.Buscar(variable,attr)){
									Error(1500);
									return false;
								}
								else if(attr.estado == null){
									Error(1600);
									return false;
								}
							}
							token=getToken();
						}
						token=getToken();
					}
					else if(token==VAR){
						//abc=160;
						//xyz=123;
						//xyz=abc;
						string tmp_var=variable;
						token=getToken();
						token=getToken();
						if(token==VAR){
							Atributos attr;
							if(!ts.Buscar(variable,attr)){
								Error(1500);
								return false;
							}
							else if(attr.estado == null){
								Error(1600);
								return false;
							}
							else{
								ts.ActualizarEstado(tmp_var,asignado);
							}
						}
						else if(token==NUM){
							ts.ActualizarEstado(tmp_var,asignado);
						}
						token=getToken();
					}
				}
			}
				
				bool Ejecucion(){
					i=0;
					int token=0;
					while(true){
						token=getToken();
						if(token==FIN){
							return true;
						}
						if(token==SUMA || token==RESTA){
							int tmp_token=token;
							string param[3];
							token=getToken();
							Atributos attr;
							for(int ii=0;ii<3;ii++){
								token=getToken();
								if(token==VAR){
									ts.Buscar(variable,attr);
									param[ii]=attr.valor;
								}
								else if(token==NUM){
									param[ii]=numero;
								}
								token=getToken();
							}
							token=getToken();
							if(tmp_token==SUMA)
								cout<<"Suma [ ";
							else
								cout<<"Resta [ ";
							for(int ii=0;ii<3;ii++){
								cout<<param[ii]<<" ";
							}
							cout<<"]"<<endl;
						}
						else if(token==MULTIPLICACION || token==DIVISION){
							int tmp_token=token;
							string param[4];
							token=getToken();
							Atributos attr;
							for(int ii=0;ii<4;ii++){
								token=getToken();
								if(token==VAR){
									ts.Buscar(variable,attr);
									param[ii]=attr.valor;
								}
								else if(token==NUM){
									param[ii]=numero;
								}
								token=getToken();
							}
							token=getToken();
							if(tmp_token==MULTIPLICACION)
								cout<<"Multiplicacion [ ";
							else
								cout<<"Division [ ";
							for(int ii=0;ii<4;ii++){
								cout<<param[ii]<<" ";
							}
							cout<<"]"<<endl;
						}
						else if(token==VAR){
							string tmp_var=variable;
							token=getToken();
							token=getToken();
							if(token==VAR){
								Atributos attr;
								if(!ts.Buscar(variable,attr)){
									Error(1500);
									return false;
								}
								else if(attr.estado == null){
									Error(1600);
									return false;
								}
								else{
									ts.ActualizarValor(tmp_var,attr.valor);
								}
							}
							else if(token==NUM){
								ts.ActualizarValor(tmp_var,numero);
							}
							token=getToken();
						}
					}
				}
					
					void Analizar() {
						cout << "ANALIZADOR LEXICO" << endl;
						if (Lexico()) {
							cout << "ANALIZADOR SINTACTICO" << endl;
							if (Sintactico()) {
								cout << "ANALIZADOR SEMANTICO" << endl;
								if (Semantico()) {
									ts.Mostrar();
									cout<<"EJECUCION" <<endl;
									if(Ejecucion()){
										ts.Mostrar();
									}
								}
							}
						}
					}
					
					void Error(int nroError){
						cout<<"Error "<<nroError<<": ";
						if(nroError==100){
							cout<<"Detallar el error 100";
						}
						else if(nroError==2000){
							cout<<"Detallar el error 2000";
						}
						else if(nroError==400){
							cout<<"Detallar el error 400";
						}
						else if(nroError==1500){
							cout<<"Detallar el error 1500";
						}
						else if(nroError==1600){
							cout<<"Detallar el error 1600";
						}
					}
};
enum TokenType {
};

struct Token {
	TokenType type;
	string value;
};

vector<Token> tokenizarCodigo(const string& codigo) {
	vector<Token> tokens;
	stringstream ss;
	string token;
};

void traducirCodigo(const vector<Token>& tokens) {
	bool esVariable = false;
	bool esNumero = false;
	bool primeraVariable = true;
	
	cout << "#include <iostream>" << endl;
	cout << "using namespace std;" << endl;
	cout << "int main() {" << endl;
	
	for (const Token& token : tokens) {
		switch (token.type) {
		case COUT:
			cout << "   cout<<";
			break;
		case CIN:
			cout << "   cin>>";
			break;
		case VAR:
			esVariable = true;
			cout << "   " << token.value;
			break;
		case NUM:
			esNumero = true;
			cout << "   " << token.value;
			break;
		case IDENTIFICADOR:
			if (esVariable) {
				cout << " " << token.value;
				esVariable = false;
				primeraVariable = false;
			} else if (esNumero) {
				cout << " = " << token.value;
				esNumero = false;
			} else {
				cout << "   " << token.value;
			}
			break;
		case IGUAL:
			cout << " =";
			break;
		case MAS:
			cout << " +";
			break;
		case MENOS:
			cout << " -";
			break;
		case POR:
			cout << " *";
			break;
		case PCOMA:
			if (primeraVariable) {
				cout << ";" << endl;
				primeraVariable = false;
			} else {
				cout << ";" << endl;
			}
			break;
		default:
			// Puedes manejar otros casos según las reglas de traducción específicas
			break;
		}
	}
	
	cout << endl << "   return 0;" << endl;
	cout << "}" << endl;
}
;

int main()
{
	Analisis* obj = new Analisis("traductor(){ num1=25; num2=35; num3=23; suma(14,15,num1); resta(20,15,num3); multiplicacion(40,num2,50,60); division(20,num1,48,60);}");
	obj->Analizar();
	delete obj;
	cout<<endl;
	cout<<endl;
	cout << "Ingrese el código en PSeInt (termina con \"FinAlgoritmo\"): " << endl;
	
	// Leer el código en PSeInt línea por línea
	string linea;
	string codigoPseint;
	while (getline(cin, linea) && linea != "FinAlgoritmo") {
		codigoPseint += linea + " ";
	}
	
	//	 Tokenizar el código
	vector<Token> tokens = tokenizarCodigo(codigoPseint);
	
	// Imprimir los tokens
	//imprimirTokens(tokens);*/
	
	cout << endl;
	
	// Traducir el código
	cout << "Código en C++:" << endl;
	traducirCodigo(tokens);
	
	return true;
}
