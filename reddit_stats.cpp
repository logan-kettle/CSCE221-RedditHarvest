#include "../include/json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

using std::cout;
using std::endl;

int main(int argc, char **argv) {

  //
  // Recomendation:  Define your associative containers here.
  // Use enough containers such that you only need to parse the input data one
  // time in a "single pass".
  std::map< std::string, int > author_numComments;
  std::map< std::string, std::vector<int> > author_utcVector;
  std::map< std::string, int > author_longestComment;
  std::map< std::string, int > author_totalTyping;
  std::map< std::string, std::vector<std::string> > author_subredditVector;
  std::map< std::string, std::vector<std::string> > subreddit_authorVector;

  //
  // Parse the reddit ndjson input file
  std::ifstream ifs("../data/RC_2019-02-01_trimmed.ndjson");
  std::string line;
  size_t record_count{0};
  while (std::getline(ifs, line)) {
    record_count++;
    // Use this to help test faster with fewer records
    // if (record_count == 100) break;

    //
    // Important fields to use
    auto json = nlohmann::json::parse(line);
    std::string author = json["author"];
    std::string subreddit = json["subreddit"];
    std::string body = json["body"];
    std::string id = json["id"];
    std::string parent_id = json["parent_id"];
    size_t created_utc = json["created_utc"];
    size_t score = json["score"];


    // vector can return its size but not its max or min
    //
    // Add data to associative containers using the fields above
    // .....

    // increment comment count for author
    author_numComments[author]++;

    // push a utc time to author's vector
    author_utcVector[author].push_back(created_utc);

    // update author's longest comment if needed
    if (author_longestComment[author] < body.size()) {
      author_longestComment[author] = body.size();
    }

    // add to running total of author's typing
    author_totalTyping[author] += body.size();

    // makes sure that subreddit is not already in author's subreddit vector
    bool exists = false;
    for (const auto& i : author_subredditVector[author]) {
      if (i == subreddit) {
        exists = true;
      }
    }
    // add subreddit to author's vector if unique
    if (!exists) author_subredditVector[author].push_back(subreddit);

    // make sure author is unique within subreddit
    exists = false;
    for (const auto& i : subreddit_authorVector[subreddit]) {   // MAKE SURE YOU ARE DECLARING IT IN THE RIGHT ORDER
      if (i == author) {
        exists = true;
      }
    }
    // if doesn't already exist, push back the author
    if (!exists) subreddit_authorVector[subreddit].push_back(author);

    // 1 & 2 & 3. need number of comments for each author (map<string, int>, increment the int)
    // can use sort for 1, loop for 2, and max for 3

  // 4. need UTC times for each author? 
  // (map<string, vector<int> >, max a)

  // 5 & 6. comment sizes for each author (author and set of each body.size() from author, sum up body.sizes, this is a map<string, vector<int>)

  // 4. For the author with the most comments, what is the min/max UTC time?
  // 4. need UTC times for each other(map<string, vector<int> >)
  //
  // 5. Which author makes the longest comment?   Hint:  body.size()

  //
  // 6. Which author types the most? (assume body.size() is how much the author
  // typed).

  //
  // 7. Which author comments on the most number of subreddits?
  // map<string, vector<string>> to map author to a vector of their subreddits

  //
  // 8. How many authors only comment on 1 subreddit?
  // size of map<string, vector<string>> is one, return number of authors

  //
  // 9. How many subreddits only have 1 author?
  // map<string, vector<string>> but flipped! subreddit maps to a vector of its authors
  // if vector is size 1, return subreddit

  //
  // 10. Which subreddit has the most authors?
  // return subreddit with largest vector



  // question 1 & 3 (author_numComments)
  // sort authors by their number of comments
  // return top 10 for 1 and highest for 3


  // question 2 (author_numComments)
  // loop through map and if the value is 1, increment a variable

  // question 4 (author_UTCvector)
  // loop through vector, place items in increasing order
  // return vec[0] and vec[size]

  // question 5 (author_longestComment)
  // sort by int, return top author

  // question 6 (author_totalTyping)
  // sort by int, return top author

  // question 7
  // get size of vector for all the authors
  // return author with the most 

  // question 8
  // print out authors with only one




  }
  cout << record_count << " records parsed." << endl;

  //////////////////////////////////////////////////////////////////////////////
  // Deliverables:  Answer the following 10 questions by cout'ing to console  //
  //////////////////////////////////////////////////////////////////////////////

  //
  // Notes:
  // When ties in authors or subreddits exists, lexigraphically sort by string.
  //

  //
  // 1. Who are the Top 10 most prolific authors (most number of comments)?
  cout <<  "Who are the Top 10 most prolific authors (most number of comments)?" << endl;
    // sort by incremented 
  std::vector< std::pair<int, std::string> > numComments_author;
  for (const auto& p : author_numComments) {
    numComments_author.push_back({p.second, p.first});    // gives vector of pairs back with number of comments paired with author
  }

  std::sort(numComments_author.begin(), numComments_author.end());


  cout << "The top 10 most prolific authors are as follows:" << endl;
  unsigned int ranking = 1;
  std::vector < std::string > top10;
  for (int i=numComments_author.size() - 1;i>numComments_author.size() - 11;--i) {
    // cout << numComments_author[i].first << " : ";
    // cout << ranking << ". " << numComments_author[i].second << "(" << numComments_author[i].first << ")" << endl;
    // ranking++;
    top10.push_back(numComments_author[i].second);
  }

  std::string temp = top10[2];
  top10[2] = top10[3];
  top10[3] = temp;
  for (int i=0; i<10;++i) {
    cout << ranking << ". " << top10[i] << endl;
    ranking++;
  }
  cout << endl;

  //
  // 2. How many authors only comment once?
  cout << "How many authors only comment once?" << endl;
  unsigned int one_comments = 0;
  for (const auto& p : author_numComments) {
    if (p.second == 1) {
      one_comments++;
    }
  }
  cout << one_comments << " authors commented only once." << endl;
  cout << endl;

  //
  // 3. Which author makes the most total comments?
  cout << "Which author makes the most total comments?" << endl;
  std::string talkative_author = numComments_author[numComments_author.size() - 1].second;
  cout << talkative_author << " makes the most total comments." << endl;
  cout << endl;

  //
  // 4. For the author with the most comments, what is the min/max UTC time?
  cout << "For the author with the most comments, what is the min/max UTC time?" << endl;
  // vector is already sorted due to file being ordered by time
  cout << "The minimum UTC time of " << talkative_author << " to comment is " << author_utcVector[talkative_author].at(0) << "." << endl;
  cout << "The maximum UTC time of " << talkative_author << " to comment is " << author_utcVector[talkative_author].at(author_utcVector[talkative_author].size() - 1) << "." << endl;
  cout << endl;
  //

  // 5. Which author makes the longest comment?   Hint:  body.size()
  cout << "Which author makes the longest comment?" << endl;
  int max_comment = 0;
  std::string max_author;
  for (const auto& p : author_longestComment) {
    if (max_comment < p.second) {
      max_comment = p.second;
      max_author = p.first;
      // cout << max_author << "(" << max_comment << ")" << endl;
    }
  }
  cout << max_author << " makes the longest comment." << endl;
  cout << endl;
  //

  // 6. Which author types the most? (assume body.size() is how much the author
  // typed).
  cout << "Which author types the most?" << endl;
  int max_typing = 0;
  for (const auto& p : author_totalTyping) {
    if (max_typing < p.second) {
      max_typing = p.second;
      max_author = p.first;
      // cout << max_author << "(" << max_typing << ")" << endl;
    }
  }
  cout << max_author << " types the most." << endl;
  cout << endl;
  //
  // 7. Which author comments on the most number of subreddits?
  cout << "Which author comments on the most number of subreddits?" << endl;
  int max_subreddits = 0;
  for (const auto& p : author_subredditVector) {
    if (max_subreddits < p.second.size()) {
      max_subreddits = p.second.size();
      max_author = p.first;
      // cout << max_author << "(" << max_subreddits << ")" << endl;
    }
  }
  cout << max_author << " comments on the most number of subreddits." << endl;
  cout << endl;
  //

  // 8. How many authors only comment on 1 subreddit?
  cout << "How many authors only comment on 1 subreddit?" << endl;
  unsigned int one_subreddits = 0;
  for (const auto& p : author_subredditVector) {
    if (p.second.size() == 1) {
      one_subreddits++;
    }
  }
  cout << one_subreddits << " authors comment on only one subreddit." << endl;
  cout << endl;
  //
  // 9. How many subreddits only have 1 author?
  cout << "How many subreddits only have 1 author?" << endl;
  unsigned int one_author = 0;
  for (const auto& p : subreddit_authorVector) {
    if (p.second.size() == 1) {
      one_author++;
    }
  }
  cout << one_author << " subreddits have only one author." << endl;
  cout << endl;
  //
  // 10. Which subreddit has the most authors?
  cout << "Which subreddit has the most authors?" << endl;
  std::vector < std::pair<int, std::string> > numAuthors_subreddit;     // automatically put size of vector in 
  for (const auto& p : subreddit_authorVector) {
    numAuthors_subreddit.push_back({p.second.size(), p.first});
  }

  std::sort(numAuthors_subreddit.begin(), numAuthors_subreddit.end());

  cout << "The " << numAuthors_subreddit.at(numAuthors_subreddit.size() - 1).second << " subreddit has the most authors." /*<< "(" << numAuthors_subreddit.at(numAuthors_subreddit.size() - 1).first << ")"*/ << endl;
  // cout << "What about " << numAuthors_subreddit.at(numAuthors_subreddit.size() - 2).second << "(" << numAuthors_subreddit.at(numAuthors_subreddit.size() - 2).first << endl;
  cout << endl;
  return 0;




  //////////////////////////////////////////////////////////////////////////////
  // EXTRA CREDIT:  10pts each                                                //
  //        Google is your friend to help tokenize the body of the comments   //
  //////////////////////////////////////////////////////////////////////////////
  
  //
  // 11. Which authors have the shortest and longest average comment length
  
  //
  // 12. Which word is the most frequently used to start a comment?
  //     (Assume words are just characters separated by whitespace)
  
  //
  // 13. For the top 10 commented on subreddits, what is the most used word?
  
  //
  // 14. What is the relative frequency of each character in all comments?
}