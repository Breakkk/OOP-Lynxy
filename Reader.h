#ifndef __READER_H__
#define __READER_H__

#include <string>

class Reader{
		private:
		public:
			Reader(std::string );
			Reader(Reader &&);
			Reader(const Reader &) = delete;
			Reader & operator= (Reader &&);
			Reader & operator= (const Reader &) = delete;
			std::string read_word();
			~Reader();
};

#endif
