#include <map>
class Ngrams 
{
   struct Ngram
   {
      std::string ngram;
      int count;
      struct Ngram * next;
	  struct Ngram * p1;
	 
   };

   typedef struct Ngram Ngram_t;

   private:
      
      Ngram_t * first;
      int ngramSz;
      void insertNgram(std::string s);
      std::string getNextNgram(WordList::const_iterator start, 
                               WordList::const_iterator end);
      void printList();
   public:
	  std::map <std::string, Ngram_t *> hash0;
	  std::vector<std::pair<std::string, int>> v;
      Ngrams(int ngramSz, const WordList & wl);
      ~Ngrams();
      void sortByCount(bool reverse);
      void printIncreasing();
      void printDecreasing();
};

