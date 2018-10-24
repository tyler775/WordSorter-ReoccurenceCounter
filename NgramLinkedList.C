#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "WordList.h"
#include "Ngrams.h"

/*
 * Ngrams
 *
 * takes as input the size of the ngrams to be built and the list  
 * of words to build the ngrams from and builds a linked list of 
 * ngrams.
 *
 * param: int ngramSz - size of the ngram
 * param: const WordList & wl - list of the words use
 */
Ngrams::Ngrams(int ngramSz, const WordList & wl)
{
   this->ngramSz = ngramSz;
   WordList::const_iterator p;
   first = NULL;
   p = wl.begin();
   while (p != wl.end())
   {
      std::string ngram = getNextNgram(p, wl.end());
      p++;
      if (!ngram.empty()) insertNgram(ngram);
   }
}

/*
 * Ngrams destructor
 *
 * automatically called when Ngrams object goes out of scope
 * deletes the linked list
 */
Ngrams::~Ngrams()
{
   Ngram_t * nextNgram;
   while (first != NULL)
   {
      nextNgram = first->next;
      delete(first);
	  
      first = nextNgram;
   }
}

/*
 * getNextNgram
 *
 * takes as input an iterator that points to the word to start the
 * ngram and an iterator that points to the end of the word list
 * and builds and returns the ngram. returns empty string if no
 * ngram can be built, for example, if there are insufficient words
 * to build one.
 *
 * param: WordList::const_iterator start - points to first word in ngram
 * param: WordList::const_iterator end - points to end of word list
 * return: std::string - returns ngram or empty string
 */
std::string Ngrams::getNextNgram(WordList::const_iterator start, 
                                 WordList::const_iterator end)
{
   int i, len;
   std::string ngram = "";
   for (i = 0; i < ngramSz && start != end; i++)
   {
      std::string word = (*start);
      //see if the string ends with punctuation
      //don't create ngrams that continue after punctuation
      if (!isalpha(word[word.length()-1]) && i < ngramSz - 1) return "";

      //take off all ending punctuation
      len = word.length() - 1;
      while (len >= 0 && !isalpha(word[len])) 
      {
         //remove last character
         word = word.substr(0, word.length() - 1);
         len--;
      }
      if (len < 0) return "";  //give up

      //is the first word in the ngram?
      if (ngram == "") ngram = word;
      else ngram = ngram + " " + word;

      start++;
   }

   //could we build a long enough ngram?
   if (i < ngramSz) return "";
size_t t0 = ngram.size();
   //take off beginning punctuation
   while (t0 > 0 && !isalpha(ngram[0])) 
      ngram = ngram.substr(1, t0);
   return ngram;
}

/*
 * insertNgram
 *
 * looks for the ngram to be inserted. If it is already in
 * the linked list,  it increments the count. If not, it 
 * inserts it into the linked list.
 *
 * param: std::string s - ngram to be inserted
 * return: none
 */
void Ngrams::insertNgram(std::string s)
{
	std::map <std::string, Ngram_t *>::iterator it;
	it = hash0.find(s);
	Ngram_t * a = new Ngram_t();
	a->ngram = s;
	a-> count = 1;
	if (it != hash0.end())
	{
		it -> second -> count++;
	}
	else{
		hash0.insert(std::pair<std::string, Ngram_t*>(s, a));
	}
	
   
}
bool wayToSort (const std::pair <std::string, int> &a, const std::pair <std::string, int> &b) { return a.second < b.second;}

/*
 * sortByCount
 *
 * performs a bubble sort on the linked list of ngrams, sorting the
 * nodes in the list by the count in increasing or decreasing
 * order of count depending upon the value of reverse
 *
 * param: reverse - true if sort should be decreasing
 * return: none (modfied private linked list)
 */
void Ngrams::sortByCount(bool reverse)
{
	for(std::map<std::string,Ngram_t *>::iterator it0 = hash0.begin(); it0 != hash0.end(); ++it0) {
  v.push_back(std::make_pair(it0->first, it0->second->count));
   
      }
	  sort(v.begin(), v.end(), wayToSort);
   
   
}

/*
 * printIncreasing
 *
 * Prints the list of ngrams in increasing order. First
 * calls sortByCount passing it the value of false, which indicates
 * that the nodes are to be sorted in increasing order of count.
 *
 */  
void Ngrams::printIncreasing()
{
   sortByCount(false);
   std::cout << "\nIncreasing list of " << ngramSz << " word ngrams and counts\n";
   std::cout << "-------------------------------------------\n";
   printList();
}

/*
 * printList
 *
 * Prints the nodes in the Ngrams linked list.
 */
void Ngrams::printList()
{
   int a = v.size();
   for (int i = 0; i < v.size(); i++)
   {
	 std::cout << v[i].first << ", " << v[i].second << std::endl;  
   }
      
  
}

/*
 * printDecreasing
 *
 * Prints the list of ngrams in decreasing order. First
 * calls sortByCount passing it the value of true, which indicates
 * that the nodes are to be sorted in decreasing order of count.
 *
 */  
void Ngrams::printDecreasing()
{
   sortByCount(true);
   std::cout << "\nDecreasing list of " << ngramSz << " word ngrams and counts\n";
   std::cout << "-------------------------------------------\n";
   printList();
}
