//#include "pch.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

vector <short int> identificacao_raio_critico(bool poro, bool matriz, vector <bool> V, vector <short int> V0, int a1, int a2, int b1, int b2, int c1, int c2, short int& rcm, long long int n)
{

	bool mark = 0;
	int i, j, k, l, AA, BB, CC, DD, EE, FF, dx, dy, dz;

	long long int aux1, aux2, aux_calculo;
	int aa, bb, cc, cont;
	cont = 0;

	if (c2 == 0)
	{
		for (i = a1; i <= a2; i++)
		{
			for (j = b1; j <= b2; j++)
			{
				aux1 = (i * (b2 + 1)) + j;


				if (V[aux1] == poro)
				{
					cont++;
					mark = 1;
					l = 0;
					while (mark > 0)
					{
						V0[aux1] = l + 1;
						if (l + 1 > rcm)
						{
							rcm = l + 1;
						}

						l = l + 1;


						AA = (i - l);
						BB = (i + l);
						CC = (j - l);
						DD = (j + l);

						if (AA < 0 || BB > a2 || CC < 0 || DD > b2)
						{
							mark = 0;
						}
						if (mark != 0)
						{
							for (aa = i - l; aa <= i; aa++)
							{
								for (bb = j - l; bb <= j; bb++)
								{

									if (sqrt((aa - i) * (aa - i) + (bb - j) * (bb - j)) <= l)
									{

										dx = j - bb;
										dy = i - aa;


										aux2 = (aa * (b2 + 1)) + bb;
										if (V[aux2] == matriz)
										{
											mark = 0;

										}

										if (dx > 0)
										{
											aux2 = (aa * (b2 + 1)) + j + dx;
											if (V[aux2] == matriz)
											{
												mark = 0;
											}

										}

										if (dy > 0)
										{
											aux2 = (i + dy) * (b2 + 1) + bb;
											if (V[aux2] == matriz)
											{
												mark = 0;
											}
										}

										if (dx > 0 && dy > 0)
										{
											aux2 = (i + dy) * (b2 + 1) + j + dx;
											if (V[aux2] == matriz)
											{
												mark = 0;
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

	else
	{
		for (i = a1; i <= a2; i++)
		{
			for (j = b1; j <= b2; j++)
			{
				for (k = c1; k <= c2; k++)
				{

					aux_calculo = k;
					aux1 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (i * (b2 + 1)) + j;


					if (V[aux1] == poro)
					{
						cont++;
						mark = 1;
						l = 0;
						while (mark > 0)
						{
							//cout << aux1 << endl;
							V0[aux1] = l + 1;
							if (l + 1 > rcm)
							{
								rcm = l + 1;
							}

							l = l + 1;


							AA = (i - l);
							BB = (i + l);
							CC = (j - l);
							DD = (j + l);
							EE = (k - l);
							FF = (k + l);

							if (AA < 0 || BB > a2 || CC < 0 || DD > b2 || EE < c1 || FF >(c2))
							{
								mark = 0;
							}
							if (mark != 0)
							{
								for (cc = k - l; cc <= k; cc++)
								{
									for (aa = i - l; aa <= i; aa++)
									{
										for (bb = j - l; bb <= j; bb++)
										{

											if (sqrt((aa - i) * (aa - i) + (bb - j) * (bb - j) + (cc - k) * (cc - k)) <= l)
											{

												dx = j - bb;
												dy = i - aa;
												dz = k - cc;


												aux_calculo = cc;
												aux2 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (aa * (b2 + 1)) + bb;
												if (V[aux2] == matriz)
												{
													mark = 0;

												}

												if (dx > 0)
												{
													aux_calculo = cc;
													aux2 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (aa * (b2 + 1)) + j + dx;
													if (V[aux2] == matriz)
													{
														mark = 0;
													}

												}

												if (dy > 0)
												{
													aux_calculo = cc;
													aux2 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (i + dy) * (b2 + 1) + bb;
													if (V[aux2] == matriz)
													{
														mark = 0;
													}
												}

												if (dx > 0 && dy > 0)
												{
													aux_calculo = cc;
													aux2 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (i + dy) * (b2 + 1) + j + dx;
													if (V[aux2] == matriz)
													{
														mark = 0;
													}
												}



												if (dz > 0)
												{
													aux_calculo = k + dz;
													aux2 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (aa * (b2 + 1)) + bb;
													if (V[aux2] == matriz)
													{
														mark = 0;
													}

												}

												if (dz > 0 && dx > 0)
												{
													aux_calculo = k + dz;
													aux2 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (aa * (b2 + 1)) + j + dx;
													if (V[aux2] == matriz)
													{
														mark = 0;
													}
												}

												if (dz > 0 && dy > 0)
												{
													aux_calculo = k + dz;
													aux2 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (i + dy) * (b2 + 1) + bb;
													if (V[aux2] == matriz)
													{
														mark = 0;
													}
												}


												if (dz > 0 && dx > 0 && dy > 0)
												{
													aux_calculo = k + dz;
													aux2 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (i + dy) * (b2 + 1) + j + dx;
													if (V[aux2] == matriz)
													{
														mark = 0;
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
	}

	printf("\nQuantidade de Pixels de Poros: %d\n", cont);
	return V0;
}
