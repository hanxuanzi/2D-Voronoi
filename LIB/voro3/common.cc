// Voro++, a 3D cell-based Voronoi library
//
// Author   : Chris H. Rycroft (LBL / UC Berkeley)
// Email    : chr@alum.mit.edu
// Date     : August 30th 2011

/** \file common.cc
 * \brief Implementations of the small helper functions. */

#include "common.hh"

namespace voro {

/** \brief Prints a vector of integers.
 *
 * Prints a vector of integers.
 * \param[in] v the vector to print.
 * \param[in] fp the file stream to print to. */
void voro_print_vector(std::vector<int> &v,FILE *fp) {
	int k=0,s=v.size();
	while(k+4<s) {
		fprintf(fp,"%d %d %d %d ",v[k],v[k+1],v[k+2],v[k+3]);
		k+=4;
	}
	if(k+3<=s) {
		if(k+4==s) fprintf(fp,"%d %d %d %d",v[k],v[k+1],v[k+2],v[k+3]);
		else fprintf(fp,"%d %d %d",v[k],v[k+1],v[k+2]);
	} else {
		if(k+2==s) fprintf(fp,"%d %d",v[k],v[k+1]);
		else fprintf(fp,"%d",v[k]);
	}
}

/** \brief Prints a vector of doubles.
 *
 * Prints a vector of doubles.
 * \param[in] v the vector to print.
 * \param[in] fp the file stream to print to. */
void voro_print_vector(std::vector<double> &v,FILE *fp) {
	int k=0,s=v.size();
	while(k+4<s) {
		fprintf(fp,"%g %g %g %g ",v[k],v[k+1],v[k+2],v[k+3]);
		k+=4;
	}
	if(k+3<=s) {
		if(k+4==s) fprintf(fp,"%g %g %g %g",v[k],v[k+1],v[k+2],v[k+3]);
		else fprintf(fp,"%g %g %g",v[k],v[k+1],v[k+2]);
	} else {
		if(k+2==s) fprintf(fp,"%g %g",v[k],v[k+1]);
		else fprintf(fp,"%g",v[k]);
	}
}

/** \brief Prints a vector a face vertex information.
 *
 * Prints a vector of face vertex information. A value is read, which
 * corresponds to the number of vertices in the next face. The routine reads
 * this number of values and prints them as a bracked list. This is repeated
 * until the end of the vector is reached.
 * \param[in] v the vector to interpret and print.
 * \param[in] fp the file stream to print to. */
void voro_print_face_vertices(std::vector<int> &v,FILE *fp) {
	int j,k=0,l;
	if(v.size()>0) {
		l=v[k++];
		if(l<=1) {
			if(l==1) fprintf(fp,"(%d)",v[k++]);
			else fputs("()",fp);
		} else {
			j=k+l;
			fprintf(fp,"(%d",v[k++]);
			while(k<j) fprintf(fp,",%d",v[k++]);
			fputs(")",fp);
		}
		while((unsigned int) k<v.size()) {
			l=v[k++];
			if(l<=1) {
				if(l==1) fprintf(fp," (%d)",v[k++]);
				else fputs(" ()",fp);
			} else {
				j=k+l;
				fprintf(fp," (%d",v[k++]);
				while(k<j) fprintf(fp,",%d",v[k++]);
				fputs(")",fp);
			}
		}
	}
}
//重载
void voro_print_face_vertices(int i, std::vector<int>& v, VoroPProperties* VoroPProperties) {
	int j, k = 0, l;
	if (v.size() > 0) {
		vector<VoroPProperties::Facevertices>tmpface;
		vector<int>tmp;
		vector<vector<int>>p_id;
		l = v[k++];
		if (l <= 1) {
			if (l == 1) //fprintf(fp, "(%d)", v[k++]);
			{
				//vector < pair<int, vector<Facevertices>>>faces;//每胞元的每个面，用角点表示
				tmp.emplace_back(v[k++]);
				p_id.emplace_back(tmp);
				tmp.clear();
			}
			else //fputs("()", fp);
			{

			}
		}
		else {
			j = k + l;
			//fprintf(fp, "(%d", v[k++]);
			tmp.emplace_back(v[k++]);
			while (k < j) //fprintf(fp, ",%d", v[k++]);
				tmp.emplace_back(v[k++]);
			//fputs(")", fp);
			p_id.emplace_back(tmp);
			tmp.clear();
		}
		while ((unsigned int)k < v.size()) {
			l = v[k++];
			if (l <= 1) {
				if (l == 1)
				{
					//fprintf(fp, " (%d)", v[k++]);
					tmp.emplace_back(v[k++]);
					p_id.emplace_back(tmp);
					tmp.clear();
				}
				else //fputs(" ()", fp);
					;
			}
			else {
				j = k + l;
				//fprintf(fp, " (%d", v[k++]);
				tmp.emplace_back(v[k++]);
				while (k < j) //fprintf(fp, ",%d", v[k++]);
					tmp.emplace_back(v[k++]);
				//fputs(")", fp);
				p_id.emplace_back(tmp);
				tmp.clear();
			}
		}
		VoroPProperties::Facevertices f_id;
		f_id.facevertices_id = p_id;
		VoroPProperties->faces.emplace_back(pair<int, VoroPProperties::Facevertices>(i, f_id));
	}

}

}
