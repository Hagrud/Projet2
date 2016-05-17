#ifndef DEF_SMT
#define DEF_SMT

#include <vector>

using namespace std;

class Smt
{
  public:
    virtual bool valid(vector<bool> result);
};


class RSmt : Smt
{
  public:
    bool valid(vector<bool> result);
    
  protected:
    void merge(int a, int b);
    int find(int a);
    void smt_union(int a, int b);
    
  private:
    vector<int> representant;
    vector<int> sig;
    vector<pair<int,int>> lambda;
};
#endif
