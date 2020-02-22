#include <iostream>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef long int li;
static li _count = 0;

class Library {
    public:
        li _numBooks;
        li _index;
        li _signUpTime;
        li _booksPerDay;
        li _totalScore;
        bool _processed;
        double _ratio;
        vector<li> _books;
        vector<li> _readBooks;

        Library () {
            _numBooks = 0;
            _signUpTime = 0;
            _booksPerDay = 0;
            _totalScore = 0;
        }

        Library (li numBooks, li signUpTime, li booksPerDay) : _numBooks(numBooks) , _signUpTime(signUpTime) , _booksPerDay(booksPerDay) {
            _index = _count++;
            _processed = false;
        }

        void setScore(li score) { 
            _totalScore = score;
        }

        bool getStatus() {
            return _processed;
        }

        void setStatus(bool s) {
            _processed = s;
        }
};

// sorting method for libraries based on their ratios
bool lib_sorter(Library *l1, Library *l2) {
    return (l1->_ratio > l2->_ratio);
}

// sorting method for books based on their score
bool books_sorter(pair<li, li> p1, pair<li, li> p2) {
    return (p1.second > p2.second);
}

// main function
int main() {
    li books = 0, num_libs = 0, days = 0; 
    cin >> books >> num_libs >> days;

    vector<pair<li, bool> > scoreBook;
    vector<Library *> libs;

    for (li i=0; i<books; ++i) {
        li score;
        cin >> score;
        scoreBook.push_back(make_pair(score, false));
    }

    // reading data for libraries
    for (li i=0; i<num_libs; ++i) {
        li b, d, c;
        cin >> b >> d >> c;
        Library *l = new Library(b, d, c);
        libs.push_back(l);
        li sum=0;
        for (li j=0; j<b; ++j) {
            li book=0;
            cin >> book;
            l->_books.push_back(book);
            sum += scoreBook[book].first;
        }
        l->setScore(sum);
        double ratio = (double)(sum*c)/d;
        l->_ratio = ratio;
        sort(libs.begin(), libs.end(), lib_sorter);     
    }

    li total_score = 0;
    li library_signedup = 0;
    li total_libs_processed = 0;

    li k = libs[library_signedup]->_signUpTime + libs[library_signedup+1]->_signUpTime;

    for (li day=(libs.front()->_signUpTime)+1; day<=days; ++day) {
        if (day == k) {
            k+=libs[library_signedup++]->_signUpTime;
        }
        
        for (li l=0; l<library_signedup; ++l) {
            if (libs[l]->getStatus()) {
                // If it's already processed continue
                continue;
            }

            vector<pair<li, li> > books_available;

            for (li m=0; m<(libs[l]->_books).size(); ++m) {
                if (!scoreBook[libs[l]->_books[m]].second) {
                    books_available.push_back(make_pair(libs[l]->_books[m], scoreBook[libs[l]->_books[m]].first));
                }    
            }

            // sorting the books based on the score
            sort(books_available.begin(), books_available.end(), books_sorter);

            li f = 0;
            for (; f < std::min( libs[l]->_booksPerDay, (li)books_available.size() ); ++f) {
                libs[l]->_readBooks.push_back(books_available[f].first);
                scoreBook[books_available[f].first].second = true;
            }

            if (f == books_available.size()) {
                libs[l]->setStatus(true);
            }
        }
    }

    for (li h=0; h<library_signedup; ++h) {
        if (libs[h]->_readBooks.size() != 0){
            total_libs_processed++;
        }
    }

    // printing output data
    cout << total_libs_processed << endl;
    for (li h=0; h<library_signedup; ++h) {
        if (libs[h]->_readBooks.size() != 0){
            cout << libs[h]->_index << " " << libs[h]->_readBooks.size() << endl;
            for (auto m = libs[h]->_readBooks.begin(); m!=libs[h]->_readBooks.end(); ++m) {
                cout << *m << " ";
            }
            cout << endl;
        }
    }

    return 0;
}