#include<bits/stdc++.h>
using namespace std;

int main() {
  string word, clean_data; //rawReviewRatings
  ifstream inFileRawReviewRatings;

  ifstream inFileStopWords; //stopwords
  string stop_word, s, s1;

  ofstream outFileCleanReviewRatings; //cleanReviewRatings
  string clean;

  inFileRawReviewRatings.open("rawReviewRatings.txt");
  if (!inFileRawReviewRatings) {
    cout << "Unable to open raw review";
    exit(1); // terminate with error
  }

  inFileStopWords.open("stopwords.txt");
  if (!inFileStopWords) {
    cout << "Unable to open stopwords";
    exit(1); // terminate with error
  }

  outFileCleanReviewRatings.open("cleanReviewRatings.txt");
  if (!inFileStopWords) {
    cout << "Unable to open clean review";
    exit(1); // terminate with error
  }

  //Store stop words in a string

  while (inFileStopWords >> s) {
    stop_word += s;
    stop_word += 32;
  }

  cout << "\n\n***********CLEAN THE DATA******************\n\n";

  while (inFileRawReviewRatings >> word) {

    int n = word.length();

    stringstream is(stop_word);

    while (is >> s1) {
      if (s1 == word)
        goto a;
    }

    for (int i = 0; i < n; i++) {
      if (word[i] == '-') //remove hyphens
      {
        clean_data += word.substr(0, i);
        clean_data += 32;
        clean_data += word.substr(i + 1, n - i + 1);
        clean_data += 32;
        goto a;
      }

      if ((word[i] == '!') || (word[i] == '"') || (word[i] == '.') || (word[i] == '\n') || (word[i] == 32)) //remove punctuation
      {
        clean_data += word.substr(0, i);
        clean_data += 32;

        goto a;

      }
    }

    if (word == "")
      goto a;

    clean_data += word;
    clean_data += 32;
    a: {}
  }

  //Store the clean review in CleanReviewRatings

  stringstream iss1(clean_data);
  string w;
  int count = 0;

  while (iss1 >> w) {
    cout << "'" << w << "'" << endl;

    outFileCleanReviewRatings << w;
    outFileCleanReviewRatings << " ";

    count++;

    if ((w == "1") || (w == "2") || (w == "3") || (w == "4") || (w == "5") || (w == "0")) {

      --count;
    }

  }

  inFileRawReviewRatings.close();
  inFileStopWords.close();

  //Unordered Map to store word rating and count

  unordered_map < string, pair < float, float >> m; //map
  unordered_map < string, pair < float, float >> ::iterator it;

  stringstream iss2(clean_data);

  vector < string > words(count); //key words
  float total_count[count] = {
    0
  }; //count of words
  float rating[count] = {
    0
  }; //individual rating of words

  int i = 0, j;
  int num;
  while (iss2 >> w) //w : split words
  {

    if ((w == "1") || (w == "2") || (w == "3") || (w == "4") || (w == "5") || (w == "0")) //if its a number then store in rating[]
    {
      if (w == "4")
        num = 4;
      else if (w == "1")
        num = 1;
      else if (w == "0")
        num = 0;
      else if (w == "2")
        num = 2;
      else
        num = 3;

    }

    if ((w == "1") || (w == "2") || (w == "3") || (w == "4") || (w == "5") || (w == "0")) {
      i--;
      goto c;
    }

    for (int j = 0; j < count; j++) //string matches with existig word
    {
      if (words[j] == w)
        goto b;
    }

    words[i] = w; //new string
    rating[i] = num;

    b: {}
    for (int j = 0; j < count; j++) //increment total count of existing string
    {
      if (w == words[j]) {
        total_count[j]++;
        break;
      }
    }
    for (int j = 0; j < count; j++) //increment rating of existing string
    {
      if (w == words[j] && i != j) {
        rating[j] += num;
        break;
      }
    }

    c: {}

    i++;

  }

  for (int k = 0; k < count; k++) {
    m.insert({
      words[k],
      make_pair(rating[k], total_count[k])
    }); //insert in map	
  }

  cout << "\n\n**************RATING AND WORD COUNT IN A MAP******************************\n\n";

  cout << setw(20) << "Word" << setw(15) << "Total_Rating" << setw(15) << "Total_Count\n\n";
  for (auto & it: m) {
    if (it.first != "")
      cout << setw(20) << it.first << setw(15) << it.second.first << setw(15) << it.second.second << endl;
  }

  //Read New Reviews from rawReviews, clean it and store it in cleanReviews

  ifstream inFileRawReviewRatingsRawReviews;
  inFileRawReviewRatingsRawReviews.open("rawReviews.txt");
  if (!inFileRawReviewRatingsRawReviews) {
    cout << "Unable to open rawReviews";
    exit(1); // terminate with error
  }

  ofstream outFileCleanReviews;
  outFileCleanReviews.open("cleanReviews.txt");
  if (!outFileCleanReviews) {
    cout << "Unable to open cleanReviews";
    exit(1); // terminate with error
  }

  vector < int > last;
  string clean_data1, clean_data2;

  //Split the data in new review and clean the data

  while (inFileRawReviewRatingsRawReviews >> word) {

    int n = word.length();
    stringstream is(stop_word);

    while (is >> s1) //if string is a stopword
    {
      if (s1 == word)
        goto x;
    }

    for (int i = 0; i < n; i++) {
      if (word[i] == '-') //remove hyphens and split as two words
      {
        clean_data1 = word.substr(0, i);
        outFileCleanReviews << clean_data1;
        outFileCleanReviews << " ";
        clean_data2 = word.substr(i + 1, n - i + 1);
        outFileCleanReviews << clean_data2;
        goto x;
      }

      if ((word[i] == '!') || (word[i] == '"') || (word[i] == '.') || (word[i] == '\n') || (word[i] == 32)) //remove punctuation
      {
        clean_data1 = word.substr(0, i);
        outFileCleanReviews << clean_data1;

        if ((word[i] == '!') || (word[i] == '.')) {
          outFileCleanReviews << "."; //dot to seperate different reviews
          outFileCleanReviews << "\r\n";
        }

        if ((word[i] == '"') && (word[i + 1] == '.')) {
          outFileCleanReviews << ".";
          outFileCleanReviews << "\r\n";
        }

        goto x;

      }

    }

    if (word == "")
      goto x;

    outFileCleanReviews << word;
    outFileCleanReviews << " ";

    x: {}
  }

  inFileRawReviewRatingsRawReviews.close();
  outFileCleanReviews.close();

  //Read from clean review and calculate the rating

  ifstream inFileRawReviewRatingsCleanReviews;
  inFileRawReviewRatingsCleanReviews.open("cleanReviews.txt");
  if (!inFileRawReviewRatingsCleanReviews) {
    cout << "Unable to open cleanReviews";
    exit(1); // terminate with error
  }

  ofstream outFileRatings;
  outFileRatings.open("ratings.txt");
  if (!outFileRatings) {
    cout << "Unable to open ratings";
    exit(1); // terminate with error
  }

  string clean2;
  int count_clean = 0, clean_length;
  float average = 0, sum = 0, sum1 = 0;
  int flag = 0;
  vector < float > ratings;

  cout << endl << endl;
  cout << "***********************RATING NEW REVIEW*****************************************";
  cout << endl << endl;
  cout << setw(20) << "Word" << setw(15) << "Word_Rating" << endl << endl;

  while (inFileRawReviewRatingsCleanReviews >> clean2) {
    if ((clean2 == ".") || (clean2 == "!")) //if punctuation is a string
    {
      average = sum / count_clean;
      cout << "RATING= " << average << endl << endl;
      outFileRatings << average;
      outFileRatings << "\r\n";
      count_clean = sum = sum1 = flag = 0;
      goto z;
    }

    flag = 0;
    clean_length = clean2.length();
    for (auto & it: m) //string matches with word in the map
    {
      if ((it.first == clean2) || (it.first == clean2.substr(0, clean_length - 1))) {
        cout << setw(20) << it.first << setw(15) << it.second.first / it.second.second << endl;
        sum1 = it.second.first / it.second.second;
        sum += sum1;
        count_clean++;
        flag++;
        break;
      }

    }

    if (flag == 0) //string does not match with word in the map..neutral rating
    {
      cout << setw(20) << clean2 << setw(15) << "2" << endl;
      sum += 2;
      count_clean++;
    }

    if ((clean2 == ".") || (clean2.substr(clean_length - 1, 1) == ".")) //punctuation is a substring
    {

      average = sum / count_clean;
      cout << "RATING= " << average << endl << endl;
      outFileRatings << average;
      outFileRatings << "\r\n";
      count_clean = sum = sum1 = flag = 0;

    }

    z: {}

  }

  outFileRatings.close();
  inFileRawReviewRatingsCleanReviews.close();
  return 0;

}
