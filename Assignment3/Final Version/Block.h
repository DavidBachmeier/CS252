class Block {

	private:
		int blockSize;
		int isValid;
		int isDirty;
		unsigned int tag;
		struct timestamp {
			int hour;
			int min;
			int sec;
			long usec;
		};

		struct timestamp timestamp;

	public:
		Block(int b);
		int getValidity();
		int getDirtiness();
		unsigned long getTag();
		int getHour();
		int getMin();
		int getSec();
		long getUsec();
		void setValidity(int validity);
		void setDirtiness(int dirtiness);
		void setTag(unsigned int tag);
		void settimestamp(int hour, int min, int sec, long usec);		

};
