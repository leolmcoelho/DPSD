//#include "pch.h"
#include <string>
//#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
using namespace std;

vector <short int> associacao_pixels_aos_raios_criticos(short int rcm, vector <short int> V0, vector <short int> V1, int a1, int a2, int b1, int b2, int c1, int c2)
{
	int i, j, k, r, dx, dy, dz;
	long long int aux1, aux2, aux_calculo;
	int aa, bb, cc;

	//Parte Bidimensional
	if (c2 == 0)
	{
		for (r = rcm - 1; r >= 0; r--)
		{

			for (i = a1; i <= a2; i++)
			{
				for (j = b1; j <= b2; j++)
				{
					aux1 = (i * (b2 + 1)) + j;

					if (V0[aux1] == r + 1)
					{
						for (aa = i - r; aa <= i; aa++)
						{
							for (bb = j - r; bb <= j; bb++)
							{
								if (sqrt((aa - i) * (aa - i) + (bb - j) * (bb - j)) <= r)
								{
									dx = j - bb;
									dy = i - aa;

									aux2 = (aa * (b2 + 1)) + bb;
									if (V1[aux2] == 0)
									{
										V1[aux2] = r + 1;
									}

									if (dx > 0)
									{
										aux2 = (aa * (b2 + 1)) + j + dx;
										if (V1[aux2] == 0)
										{
											V1[aux2] = r + 1;
										}

									}

									if (dy > 0)
									{
										aux2 = (i + dy) * (b2 + 1) + bb;
										if (V1[aux2] == 0)
										{
											V1[aux2] = r + 1;
										}
									}

									if (dx > 0 && dy > 0)
									{
										aux2 = (i + dy) * (b2 + 1) + j + dx;
										if (V1[aux2] == 0)
										{
											V1[aux2] = r + 1;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	//Parte Tridimensional
	else
	{
		for (r = rcm - 1; r >= 0; r--)
		{

			for (i = a1; i <= a2; i++)
			{
				for (j = b1; j <= b2; j++)
				{
					for (k = c1; k <= c2; k++)
					{
						aux_calculo = k;
						aux1 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (i * (b2 + 1)) + j;

						if (V0[aux1] == r + 1)
						{
							for (cc = k - r; cc <= k; cc++)
							{
								for (aa = i - r; aa <= i; aa++)
								{
									for (bb = j - r; bb <= j; bb++)
									{
										if (sqrt((aa - i) * (aa - i) + (bb - j) * (bb - j) + (cc - k) * (cc - k)) <= r)
										{
											dx = j - bb;
											dy = i - aa;
											dz = k - cc;

											aux_calculo = cc;
											aux2 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (aa * (b2 + 1)) + bb;
											if (V1[aux2] == 0)
											{
												V1[aux2] = r + 1;
											}

											if (dx > 0)
											{
												aux_calculo = cc;
												aux2 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (aa * (b2 + 1)) + j + dx;
												if (V1[aux2] == 0)
												{
													V1[aux2] = r + 1;
												}

											}

											if (dy > 0)
											{
												aux_calculo = cc;
												aux2 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (i + dy) * (b2 + 1) + bb;
												if (V1[aux2] == 0)
												{
													V1[aux2] = r + 1;
												}
											}

											if (dx > 0 && dy > 0)
											{
												aux_calculo = cc;
												aux2 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (i + dy) * (b2 + 1) + j + dx;
												if (V1[aux2] == 0)
												{
													V1[aux2] = r + 1;
												}
											}



											if (dz > 0)
											{
												aux_calculo = k + dz;
												aux2 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (aa * (b2 + 1)) + bb;
												if (V1[aux2] == 0)
												{
													V1[aux2] = r + 1;
												}

											}

											if (dz > 0 && dx > 0)
											{
												aux_calculo = k + dz;
												aux2 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (aa * (b2 + 1)) + j + dx;
												if (V1[aux2] == 0)
												{
													V1[aux2] = r + 1;
												}
											}

											if (dz > 0 && dy > 0)
											{
												aux_calculo = k + dz;
												aux2 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (i + dy) * (b2 + 1) + bb;
												if (V1[aux2] == 0)
												{
													V1[aux2] = r + 1;
												}
											}


											if (dz > 0 && dx > 0 && dy > 0)
											{
												aux_calculo = k + dz;
												aux2 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (i + dy) * (b2 + 1) + j + dx;
												if (V1[aux2] == 0)
												{
													V1[aux2] = r + 1;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return V1;
}