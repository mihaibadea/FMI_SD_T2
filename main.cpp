#include <iostream>
#include <cstdlib>
#include <ctime>


class SkipList
{
    public:
        SkipList()
        {
           srand(time(nullptr));
           start = new Node(0,level_max);
           level = 0;
        }
        ~SkipList()
        {
            delete start;
        }
        void add(int x)
        {
            Node *tmp = start;
            Node *deac[level_max+1];
            for(int i=0; i<=level_max; i++)
            {
                deac[i]=nullptr;
            }

            for(int i=level; i>=0; i--)
            {
                while(tmp->next[i]!=nullptr && tmp->next[i]->value < x)
                {
                    tmp=tmp->next[i];
                }
                deac[i]=tmp;
            }
            tmp=tmp->next[0];


            int new_level = get_level();

            if(new_level>level)
            {
                for(int i=level+1; i<=new_level; i++)
                {
                    deac[i]=start;
                }
                level=new_level;
            }

            tmp = new Node(x, new_level);
            for(int i=0; i<=new_level; i++)
            {
                tmp->next[i] = deac[i]->next[i];
                deac[i]->next[i]=tmp;
            }

            std::cout<<"L-am adaugat pe "<<x<<" in lista.\n";

        }
        void rem(int x)
        {

            bool del = 1;

            while(del)
            {
                Node *tmp = start;
                Node *deac[level_max+1];

                del=0;

                for(int i=0; i<=level_max; i++)
                {
                    deac[i]=nullptr;
                }

                for(int i=level; i>=0; i--)
                {
                    while(tmp->next[i]!=nullptr && tmp->next[i]->value < x)
                    {
                        tmp=tmp->next[i];
                    }
                    deac[i]=tmp;
                }

                tmp=tmp->next[0];

                if(tmp!=nullptr && tmp->value == x)
                {
                    int l=0;
                    while(l<=level && deac[l]->next[l]==tmp)
                    {
                        deac[l]->next[l]=tmp->next[l];
                        l++;
                    }

                    delete tmp;
                    while(level>0 && start->next[level]==nullptr)
                    {
                        level--;
                    }
                    del=1;
                    std::cout<<"L-am sters pe "<<x<<" din lista.\n";
                }

            }

        }
        void exists(int x)
        {
            Node *tmp = start;
            for(int i=level; i>=0; i--)
            {
                while(tmp->next[i]!=nullptr && tmp->next[i]->value < x)
                {
                    tmp=tmp->next[i];
                }
            }
            tmp=tmp->next[0];
            if(tmp==nullptr)
            {
                std::cout<<"Numarul "<<x<<" nu este in lista.\n";
            }
            else
            {
                if(tmp->value == x)
                {
                    std::cout<<"Numarul "<<x<<" este in lista.\n";
                }
                else std::cout<<"Numarul "<<x<<" nu este in lista.\n";
            }
        }
        void pred(int x)
        {
            Node *tmp = start;
            for(int i=level; i>=0; i--)
            {
                while(tmp->next[i]!=nullptr && tmp->next[i]->value < x)
                {
                    tmp=tmp->next[i];
                }
            }
            if(tmp!=nullptr && tmp!=start)
            {
                std::cout<<"Predecesorul lui "<<x<<" este "<<tmp->value<<".\n";
            }
            else
            {
                std::cout<<"Numarul "<<x<<" nu are predecesor.\n";
            }
        }
        void succ(int x)
        {
            Node *tmp = start;
            for(int i=level; i>=0; i--)
            {
                while(tmp->next[i]!=nullptr && tmp->next[i]->value <= x)
                {
                    tmp=tmp->next[i];
                }
            }

            tmp=tmp->next[0];

            if(tmp!=nullptr)
            {
                std::cout<<"Succesorul lui "<<x<<" este "<<tmp->value<<".\n";
            }
            else
            {
                std::cout<<"Numarul "<<x<<" nu are succesor.\n";
            }

        }
        void show(int x, int y)
        {
            std::cout<<"In intervalul ["<<x<<", "<<y<<"] sunt urmatoarele numere din lista: ";
            Node *tmp = start;
            for(int i=level; i>=0; i--)
            {
                while(tmp->next[i]!=nullptr && tmp->next[i]->value < x)
                {
                    tmp=tmp->next[i];
                }
            }
            tmp=tmp->next[0];

            while(tmp!=nullptr && tmp->value <=y)
            {
                std::cout<<tmp->value<<' ';
                tmp=tmp->next[0];
            }
            std::cout<<'\n';
        }

    private:
        class Node
        {
            public:
                Node(int v, int level)
                {
                    next = new Node*[level+1];
                    for(int i=0; i<level+1; i++)
                    {
                        next[i]=nullptr;
                    }
                    this->value = v;
                }
                ~Node()
                {
                    delete [] next;
                }
                int value;
                Node **next;
        };
        Node *start;
        int level;
        int level_max=5;
        int get_level()
        {
            return rand()%level_max+1;

        }
};

int main()
{

    SkipList L;

    std::cout<<"Operatiile posibile sunt urmatoarele:\n"
             <<"1 x - introduceti x in lista\n"
             <<"2 x - eliminati toate aparitiile lui x din lista\n"
             <<"3 x - verificati daca x este in lista\n"
             <<"4 x - afisati succesorul lui x din lista\n"
             <<"5 x - afisati predecesorul lui x din lista\n"
             <<"6 x y - afisati numerele din intervalul [x, y] care sunt in lista\n"
             <<"7 - incheiati executia programului\n"
             <<"\n";

    bool fin = false;

    while(!fin)
    {
        std::cout<<"Alegeti o optiune: ";

        int option, x, y;

        std::cin>>option;


        switch(option)
        {
            case 1:
                std::cin>>x;
                L.add(x);
                break;
            case 2:
                std::cin>>x;
                L.rem(x);
                break;
            case 3:
                std::cin>>x;
                L.exists(x);
                break;
            case 4:
                std::cin>>x;
                L.succ(x);
                break;
            case 5:
                std::cin>>x;
                L.pred(x);
                break;
            case 6:
                std::cin>>x>>y;
                L.show(x,y);
                break;
            case 7:
                std::cout<<"Multumim. Va mai asteptam pe la noi!\n";
                fin=true;
                break;
            default:
                std::cout<<"Va rugam incercati din nou.\n";
        }
    }

    return 0;
}
