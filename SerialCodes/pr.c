/*
 * relax.c
 * 
 * Copyright 2018 Vitor <vitor@vitor-mazon>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void mascara(double **M, double xdim, double ydim) {
	int i, j;
	
	for(i=0; i<xdim; i++) {
		for(j=0; j<ydim; j++) {
			M[i][j]=0;
			if(i<(int)(xdim-1)/2 && j==(int)(ydim-1)/2)
				M[i][j]=1;
		}
	}
	return;
}

void condContorno(double **M, int idim, int jdim, double xi, double xf, double yi, double yf) {
	int i, j;
	double hx, hy, t;
	
	hx=(xf-xi)/idim;
	hy=(yf-yi)/jdim;
	
	for(i=0; i<idim; i++) 
		for(j=0; j<jdim; j++) {
			M[i][j]=0;
		}
	
	t=xi;
	for(i=0; i<idim; i++) {
		M[i][0]=0;
		M[i][jdim-1]=0;
		t+=hx;
	}
	
	t=yi;
	for(j=0; j<jdim; j++) {
		M[0][j]=0;
		M[idim-1][j]=200;
		t+=hy;
	}
	return;
}

int relax(double **M, int idim, int jdim, double h) {
	int i, j, cont=0;
	int x, y;
	double var=h, aux;
	double f=1.;	//Função da equação diferencial, edp=f (Poisson)
	
	x=idim-1;
	y=jdim-1;
	
	//h é a precisão do valor da matriz
	while(var>=h) {
		var=0.;
		for(i=1; i<x; i++) {
			for(j=1; j<y; j++) {
				aux=M[i][j];
				if(M[i][j]!=1.)
					M[i][j]=(M[i-1][j]+M[i+1][j]+M[i][j-1]+M[i][j+1]-f)/4;
				//if(i<(int)(idim-1)/2 && j==(int)(jdim-1)/2)
				//	M[i][j]=1;
				if(fabs(aux-M[i][j])>var)
					var=fabs(aux-M[i][j]);
			}
		}
		cont++;
	}
	return cont;
}

void imprime(double **N, int x, int y){
	int i, j;
	for(i=0;i<x;i++) {
		for(j=0;j<y;j++) { 
			printf("%5.2lf\t",N[i][j]);
		}	  
		puts("");
	}
}

int main(int argc, char **argv) {
	int idim, jdim, it, i;
	double **L, err, xi, xf, yi, yf;
	
	clock_t begin = clock();
	
	//Dominio
	xi=0;
	xf=2;
	yi=0;
	yf=2;
	
	err=atof(argv[1]);
	idim=102*(yf-yi);
	jdim=102*(xf-xi);
	
	L=malloc(idim*sizeof(double *));
	for(i=0; i<idim; i++)
		L[i]=(double *)malloc(jdim*sizeof(double *));
	
	mascara(L, idim, jdim);	
	//condContorno(L, idim, jdim, xi, xf, yi, yf);
	//imprime(L, idim, jdim);
	//it=relax(L, idim, jdim, err);
	imprime(L, idim, jdim);
	//printf("# %d iterações\n", it);
/*	
	clock_t end = clock();
	double tempo = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("# tempo = %lf\n", tempo);
*/
	free(L);
	
	return 0;
}
