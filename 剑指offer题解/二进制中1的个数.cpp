/************************************************************* 
 * 面试题10：二进制中1的个数P80页的解法很经典
 * Edit by changmu
 *************************************************************/ 

int NumberOf1(int n) 
{
	int cnt = 0;
	while (n) {
		++cnt;
		n &= (n - 1);
	}

	return cnt;
}
