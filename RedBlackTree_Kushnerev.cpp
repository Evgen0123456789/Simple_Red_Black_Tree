#include <iostream>
#include <string>

using namespace std;

class Node { //решил поупражняться заодно и в насследование - реализую базовый класс вершины и наследника - цветную вершину
	private:
		
		Node *left_child;
		Node *right_child;
		Node *parent;
		
		int value;
		char Color;
		string word; // Считаем, что дерево - список слов с возможными повторениями. Нам же что-нибудь в нём нужно хранить.
	
		bool isBalansed(){// проверяем на отсутствие у красной вершины красного потомка или на отсатствие двух красных братьев.
			bool flag = true;
			if (this->Color == 'B')
			{
				flag = (this->left_child==nullptr 
						|| this->right_child == nullptr
						|| this->right_child->Color!='R'
						|| this->left_child->Color!='R');
			} else {
				flag =  (this->left_child==nullptr 
						|| this->left_child->Color!='R') &&
						(this->right_child == nullptr
						|| this->right_child->Color!='R');
			}
			return flag;
		}
			
	
		bool CanBeDecendant(int v) {
			return (   this->left_child  != nullptr && this->value > v
					|| this->right_child != nullptr && this->value < v);
		}
	
		
		Node* GetAppropriateNode(int v){ 
			/* поиск вершины, для которой v - либо её ключ, 
			либо может быть создан потомок со ключом, равным v*/
			if (this->value == v) {
				//cout << "Count of itterations: 0\n";
				return this;
			}
			
			Node *current_node = this;
			int count_of_itterations = 0;
			
			while (current_node->CanBeDecendant(v)){
				count_of_itterations++;
				if (current_node->value < v){
					current_node = current_node->right_child;
				} else {
					current_node = current_node->left_child;
				}
			}
			
			//cout << "Count of itterations: " << count_of_itterations << '\n';
			return current_node;
		}
		
		void LeftRotation(){
			//cout << "Lrot" << endl;
			/*происходит, если левый потомок красной вершины - красный; не совсем поворот, но его включает
			  Если нарисовать две иакие вершины, их чёрного предка и всех детей/братьев 1-ого поколения,
			  то получится 2 дерева по 7 вершин - однозначно приводятся к идиально сбаланс. бин. дереву. Пример (штрих - красная вершина,
			  заглавная буква - указатель, строчная - значение):
					    Gg
					   /  \							 Ge
	   current node-> Ee' Ff		----->    	    /  \
					 /  \						  Cc'   Eg' <-current node
			        Cc'  Dd		    ----->		 / \   /  \
				   /  \							Aa Bb Dd  Ff
			     Aa   Bb
				 
				   G						        C
				  / \						       / \
				 F  E'<-c.n.    ----->		      G'  E'<-c.n.
				   / \						     / \ / \
				  C'  D						    F  A B  D
				 / \    	    ----->		
				A   B 					
				 
				 
				 
				 
			получается, перекраски не происходит. Во втором случае много перемещений.
			Т.к. корень инициализируется как постоянная, то вершину G не перемещаем,
			только обмениваем содержимое. */
			
			if (this->parent->left_child != nullptr && this==this->parent->left_child){
				Node *C, *D, *E, *F, *G; // правого потомка наша вершина гарантировано сохранит
				
				C = this->left_child;
				D = this->right_child;
				E = this;
				G = this->parent;
				F = this->parent->right_child;
				
				G->left_child = C;
				G->right_child = E;
				E->left_child = D;
				E->right_child = F;
				
				if (C!=nullptr) C->parent = G;
				if (F!=nullptr) F->parent = E;
				
				int v = E->value;
				string w = E->word;
				
				E->value = G->value;
				E->word = G->word;
				
				G->value = v;
				G->word = w;
				
			} else {
				Node *A, *B, *C, *E, *F, *G; // правого потомка наша вершина гарант. сохранит
				
				A = this->left_child->left_child;
				B = this->left_child->right_child;
				C = this->left_child;
				E = this;
				G = this->parent;
				F = this->parent->left_child;
				
				G->left_child = C;
				C->left_child = F;
				C->right_child = A;
				E->left_child = B;
				
				
				if (C!=nullptr) C->parent = G;
				if (F!=nullptr) F->parent = C;
				if (B!=nullptr) B->parent = E;
				
				int v = C->value;
				string w = C->word;
				
				C->value = G->value;
				C->word = G->word;
				
				G->value = v;
				G->word = w;
				
			}			
		}
			
		
		
		void RightRotation(){ // Симмметрично
			//cout << "Rrot" << endl;
			if (this->parent->right_child != nullptr && this==this->parent->right_child){
				Node *C, *D, *E, *F, *G; // правого потомка наша вершина гарант. сохранит
				
				C = this->right_child;
				D = this->left_child;
				E = this;
				G = this->parent;
				F = this->parent->left_child;
				
				G->right_child = C;
				G->left_child = E;
				E->left_child = F;
				E->right_child = D;
				
				if (C!=nullptr) C->parent = G;
				if (F!=nullptr) F->parent = E;
				
				int v = E->value;
				string w = E->word;
				
				E->value = G->value;
				E->word = G->word;
				
				G->value = v;
				G->word = w;
				
			} else {
				Node *A, *B, *C, *E, *F, *G; // правого потомка наша вершина гарант. сохранит
				
				A = this->left_child->left_child;
				B = this->left_child->right_child;
				C = this->left_child;
				E = this;
				G = this->parent;
				F = this->parent->left_child;
				
				G->right_child = C;
				C->right_child = F;
				C->left_child = B;
				E->right_child = A;
				
				if (C!=nullptr) C->parent = G;
				if (F!=nullptr) F->parent = C;
				if (A!=nullptr) A->parent = E;
				
				int v = C->value;
				string w = C->word;
				
				C->value = G->value;
				C->word = G->word;
				
				G->value = v;
				G->word = w;
				
			}		
			
		}
	
		void RedUp(){ // Если оба потомка красные, то перекрашиваем участок.
			//cout << "redUp" << endl;
			this->left_child->Color = 'B';
			this->right_child->Color = 'B';
			this->Color = (this->parent == nullptr) ? 'B' : 'R';

		}
		
	
		void MakeBalansedAfterAdding(){ // вызывается при добавлении
			bool unbalanced = true;
			Node * node = this;
			//int k = 0;
			while (!node->isBalansed()){
				//cout << k++ << endl;
				if (node->left_child!=nullptr && node->left_child->Color=='R'
					&& node->right_child!=nullptr && node->right_child->Color=='R') node->RedUp();
				else if (node->left_child!=nullptr && node->left_child->Color=='R') node->LeftRotation();
				else if (node->right_child!=nullptr && node->right_child->Color=='R') node->RightRotation();
					
				if (node->parent == nullptr) break;
				else node = node->parent;
				//cout << k - 0.5 << endl;
			}
		}
	
		void MakeBalansedAfterDeleting(bool left_flag) { // флаг - память о нисходящей ветке с недостатком вершин. Левый - значит, недостаток слева.
			// Самый сложный момент. Поднимаемся вверх пока не попадётся красная вершина/корень, а основания побочных ветвей или окрасняем,
			// или (если уже красные) рекомбинируем с перекраской. При этом проверяем и восстанавливаем баланс в окрестносятях.
			// При перекраски чёрного в красный просто балансируем перекрашенную вершину. Ребалансировка затрагивает только окрестности. При этом между 
			// веткой удалений и текущей вершиной (потомка которой балансируем) вставляется красная вершина. И балансируемая вершина - тоже красная. Перекрашиваем.
			// И здесь можно заметить, что корень поддерева - красный, само оноо сбалансированное. Значит, этот корень перекрашиваем в чёрный - и баланс восстановлен
			bool flag = left_flag;
			int k = 0;
			
			//cout << this->value << ' ' << this->left_child << ' ' << this->right_child;
			
			Node* node = this;
			
			while (node->Color == 'B' && node->parent!=nullptr)
			{
				//cout << '|' << k++ << '\n';
				cout << node->value << ' ' << node->left_child << ' ' << node->right_child << endl;
				if (flag){
					//cout << node->right_child->value << node->right_child->Color << endl;
					if (node->right_child->Color == 'B'){
						//cout << "before swap" << node->right_child->Color <<endl;
						node->right_child->Color = 'R';
						//cout << "after  swap" << node->right_child->Color<<endl;
						if (node->right_child->right_child != nullptr && 
							node->right_child->right_child->Color == 'R') {
								node->right_child->RightRotation();
								node->RedUp();
								node->Color = 'B';
								break;
							}

						else if (node->right_child->left_child != nullptr && 
							node->right_child->left_child->Color == 'R') {
								node->right_child->LeftRotation();
								node->RedUp();
								node->Color = 'B';
								break;
							}


					} else {
						Node *A, *B, *C, *D, *E, *F, *G;
						G = node;
						A = node->left_child;
						F = node->right_child;
						D = node->right_child->left_child;
						B = node->right_child->left_child->left_child;
						C = node->right_child->left_child->right_child;
						E = node->right_child->right_child;

						E->Color='R'; // В данном случае балансировка по удалению завершится, но нужно потом сбалансировать по цвету E. 
						// правда, её родитель, его родитель и собрат, кузены - все зелёные, поэтому перебаланс будет полностью локальным. Разве что F перекраситсся.

						D->left_child = A;
						D->right_child = B;
						G->left_child = D;
						F->left_child = C;

						A->parent = D;
						D->parent = G;
						C->parent = F;

						int v = G->value;
						string w = G->word;

						G->value = D->value;
						G->word = D->word;

						D->word = w;
						D->value = v;

						F->Color = 'B';
						D->Color = 'B';

						if (C->Color=='R') F->RedUp();
						else if (E->left_child!=nullptr && E->left_child->Color == 'R') E->LeftRotation();
						else if (E->right_child!=nullptr && E->right_child->Color == 'R') E->RightRotation();

						break;
					}

				} else {
					if (node->left_child->Color == 'B'){
						node->left_child->Color = 'R';
						if (node->left_child->right_child != nullptr && 
							node->left_child->right_child->Color == 'R') {
								node->right_child->RightRotation();
								node->RedUp();
								node->Color = 'B';
								break;
							}

						else if (node->left_child->left_child != nullptr && 
							node->left_child->left_child->Color == 'R') {
								node->right_child->LeftRotation();
								node->RedUp();
								node->Color = 'B';
								break;
							}
						

					} else {
						Node *A, *B, *C, *D, *E, *F, *G;
						
						G = node->right_child;
						A = node->left_child->left_child;
						F = node;
						D = node->left_child->right_child;
						B = node->left_child->right_child->left_child;
						C = node->left_child->right_child->right_child;
						E = node->left_child;

						E->Color='R';

						F->right_child = D;
						D->right_child = G;
						E->right_child = B;
						D->left_child = C;

						B->parent = E;
						G->parent = D;
						D->parent = F;

						int v = F->value;
						string w = F->word;

						F->value = D->value;
						F->word = D->word;

						D->word = w;
						D->value = v;

						E->Color = 'B';
						D->Color = 'B';

						if (B->Color=='R') E->RedUp();
						else if (A->left_child!=nullptr && A->left_child->Color == 'R') A->LeftRotation();
						else if (A->right_child!=nullptr && A->right_child->Color == 'R') A->RightRotation();

						break;
					}

				}
				
				flag = node->parent->left_child==node;
				node = node->parent;
			}
			cout << "Out of Cycle\n";
			//node->WriteTree();
			cout << node->value << ' ' << node->left_child << ' ' << node->right_child << endl;
			
			
			if (node->Color == 'R' || node->parent == nullptr){
				node->Color = 'B';
				if (flag){
					node->right_child->Color = 'R';
					if (node->right_child->right_child != nullptr && 
						node->right_child->right_child->Color == 'R') {
							node->right_child->RightRotation();
							node->RedUp();
							node->Color = 'B';
						}

						else if (node->right_child->left_child != nullptr && 
							node->right_child->left_child->Color == 'R') {
								node->right_child->LeftRotation();
								node->RedUp();
								node->Color = 'B';
							}
				} else {
					node->left_child->Color = 'R';
					if (node->left_child->right_child != nullptr && 
						node->left_child->right_child->Color == 'R') {
							node->left_child->RightRotation();
							node->RedUp();
							node->Color = 'B';
						}

						else if (node->left_child->left_child != nullptr && 
							node->left_child->left_child->Color == 'R') {
								node->left_child->LeftRotation();
								node->RedUp();
								node->Color = 'B';
							}
					
					
					
				}
					
				
			}
		}
	
	public:
		Node(int v, string w = "NULL", Node *p = nullptr) {
			this->value = v;
			this->left_child = nullptr;
			this->right_child = nullptr;
			this->parent = p;
			this->word = w;
			
			if (p==nullptr) this->Color = 'B';
			else 			this->Color = 'R';
		}
		
		~Node(){
			if (this->left_child  != nullptr) delete this->left_child;
			if (this->right_child != nullptr) delete this->right_child;
			if (this->parent != nullptr){
				if (this->parent->left_child == this) this->parent->left_child = nullptr;
				else this->parent->right_child = nullptr;
			}
			cout << "Node Numbere "<< this->value << " has been deleted\n";
			cout << "Word: " << this->word << '\n';
		}
		
		void WriteTree(){
			
			cout << this->value << '\t' << this->Color << '\t' << this->word;
			if (this->left_child  != nullptr) cout << '\t' << this->left_child->value;
			if (this->right_child != nullptr) cout << '\t' << this->right_child->value;
			cout << endl;
			
			if (this->left_child  != nullptr) this->left_child->WriteTree();
			if (this->right_child != nullptr) this->right_child->WriteTree();
		}
		
		int GetSize() {
			int a = 0, b = 0;
			if (this->left_child  != nullptr) a = this->left_child->GetSize();
			if (this->right_child != nullptr) b = this->right_child->GetSize();
			return a + b + 1; 
		}
	
		int GetDepth() {
			int a = 0, b = 0;
			if (this->left_child  != nullptr) a = this->left_child->GetDepth();
			if (this->right_child != nullptr) b = this->right_child->GetDepth();
			return (a>b)?a:b+1; 
		}
		
		string GetWordByValue(int v){
			Node *node = this->GetAppropriateNode(v);
			if (node->value==v) return node->word;
			
			cout << "Word number " << v << " doesn't exist!\n Empty word has been returned.\n";
			return "";
		}
		
		void AddValue(int v, string w){
			Node *node = this->GetAppropriateNode(v);
			
			if (node->value == v) {
				cout << "Data has just been changed.\n";
				node->word = w;
			} else {
				Node *child = new Node(v, w, node);
				cout << "Data has just been added.\n";
				if (node->value < v) node->right_child = child;
				else node->left_child = child;
				
				node->MakeBalansedAfterAdding();
			}
		}
		
		void DelValue(int v){ // при удалении будем заменять на левого потомка (если есть выбор)
			Node *node = this->GetAppropriateNode(v);
			string word = node->word;
			
			if (node->value == v) {
				
				bool left_flag = true;
				
				if (node->right_child != nullptr){ // пробуем спуститься вправо и до упора влево. В итоге "визуально" удаляем вершину с хотя бы одним листом.
					Node * down = node;
					down = node->right_child;
					
					while (down->left_child != nullptr) down = down->left_child;
					
					left_flag = down != node->right_child;
					
					node->value = down->value;
					node->word = down->word;
					
					node = down; //своп и перескок
					
					node->value = v;
					node->word = word; //для корректности текста при удалении
					
				}
				
				
				if (node->Color == 'R') { // в этом случае просто удаляем
					if(left_flag) node->parent->left_child = nullptr;
					else node->parent->right_child = nullptr;
										
					delete node;
					
				} else if (node->right_child != nullptr){ // т. к.  спустились к вешине с 1 листом, то другой потомок - красный
					node->word = node->right_child->word;
					node->value = node->right_child->value;
					
					node = node->right_child;
					
					node->value = v;
					node->word = word;
							
					delete node;					
					
				} else if (node->left_child != nullptr){
					node->word = node->left_child->word;
					node->value = node->left_child->value;
					
					node = node->left_child;
					
					node->value = v;
					node->word = word;
							
					delete node;
				} else {
					node->value = v;
					node->word = word;
					Node * parent = node->parent;
					
					parent->MakeBalansedAfterDeleting(left_flag);
					delete node;
				}
			}
			else cout << "Wrong! word number " << v << " doesn't exist!\n";
			
		}
		

};


int main() {
	int v;
	bool flag = true;
	string word;
	char command = 'B';
	cout << "Start\nPlease, enter root\n";
	cin >> v >> word;
	Node *Root = new Node(v, word);
	cout << "Now, to add node write '+ value word',\n\
to get word write 'f value',\n\
to get depth write 'd',\n\
to get size write 's', \n\
to get all tree write 'w',\n\
to delete node write '- value'\n\
to exit write 'e'.\n";
	
	while (flag){
		cin >> command;
		
		switch(command){
			case '+':{
				cin >> v >> word;
				Root->AddValue(v, word);
				break;
			}
			case 'f':{
				cin >> v;
				cout << Root->GetWordByValue(v);
				break;
			}
			case 'd':{
				cout << Root->GetDepth();
				break;
			}
			case 's':{
				cout << Root->GetSize();
				break;
			}
			case 'w':{
				Root->WriteTree();
				break;
			}
			case '-':{
				cin >> v;
				Root->DelValue(v);
				break;
			}
			case 'e':{
				flag = false;
				break;
			}
			
			default: cout << "Incorrect command!";
		}
		
		cout << '\n';
	}
	return 0;
}