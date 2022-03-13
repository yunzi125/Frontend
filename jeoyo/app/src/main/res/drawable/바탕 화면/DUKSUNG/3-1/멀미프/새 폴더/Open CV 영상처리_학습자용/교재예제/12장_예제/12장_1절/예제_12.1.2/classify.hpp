vector<int> grouping(vector<Mat> hists)
{
	Matx<float,32,1> w[2], s[2];
	w[0] << 0,0,2,2,3,5,5,4,4,3,3,2,1,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,3,3,2;
	w[1] << 0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,6,5,4,3,2,1,0,0,0,0,0,0;
	
	vector<int> groups;
	for (int i = 0; i < (int)hists.size(); i++)
	{
		multiply(w[0], hists[i], s[0]);				// 히스토그램 유사도
		multiply(w[1], hists[i], s[1]);

		int group = (sum(s[0])[0] > sum(s[1])[0]) ? 0 : 1;
		groups.push_back(group);
	}
	return groups;
}


void classify_coins(vector<RotatedRect> circles, vector<int>& groups, int Ncoins[4])
{
	for (int i = 0; i < (int)circles.size(); i++)
	{
		int coin = 0;
		int radius = cvRound(circles[i].angle);

		if (groups[i] == 0) {
			if (radius > 48)		coin = 3;
			else if (radius > 46)	coin = 2;
			else if (radius > 25)	coin = 0;
		}
		if (groups[i] == 1) {
			if (radius > 48)		coin = 3;
			else if (radius > 43)	coin = 2;
			else if (radius > 36)	coin = 1;
		}

		Ncoins[coin]++;
	}
}

int calc_coins(int Ncoins[4])
{
	int count = 0;
	int coin_value[] = { 10, 50, 100, 500 };

	for (int i = 0; i< 4; i++) {
		count += coin_value[i] * Ncoins[i];

		cout << format("%3d원: %3d 개", coin_value[i], Ncoins[i]) << endl;
	}
	return count;
}