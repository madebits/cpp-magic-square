// (c) copyright - Vasian Cepa

function CreateMatrix(n)
{
	if(n <= 0) return null;
	if((n % 2) == 0) return null;
	var m = new Array(n);
	for(var i = 0; i < n; i++)
	{
		m[i] = new Array(n);
	}

	for(var i = 0; i < n; i++)
	{
		for(var j = 0; j < n; j++)
		{
			m[i][j] = 0;
		}

	}
	return m;
}

function FillTable(n)
{
	var i = 0, k = 0, j = 0;
	var n2 = n*n;
	var m = CreateMatrix(n);

	j = (n-1)/2;
	while(k++ < n2){
		//SetElement(i, j, k);
		m[i][j] = k;
		if(i==0){
			if(j == n - 1) i++;
			else{
				i = n - 1;
				j++;
			}
		} else {
			if(j == n - 1){
				i--;
				j = 0;
			} else {
				if(m[i-1][j+1] == 0)
				{
					i--;
					j++;
				} else {
					i++;
				}
			}
		}
	}
	return m;
}
