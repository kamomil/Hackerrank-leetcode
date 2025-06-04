class DisJointSets{

private:
  class setNode{
    
  public:
    int parent;
    int rank;
    
  };
  
  setNode* sets;
  
public:
  DisJointSets(int sz);
  ~DisJointSets();
  int find(int a);
  void union_sets(int a,int b);
};
