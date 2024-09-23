// Tetrahedron example code
//
// Author   : Chris H. Rycroft (LBL / UC Berkeley)
// Email    : chr@alum.mit.edu
// Date     : August 30th 2011

#include "src\voro++.hh"
using namespace voro;

// 为容器几何设置常量
const double x_min=-2,x_max=2;
const double y_min=-2,y_max=2;
const double z_min=-2,z_max=2;

// 设置容器划分的块的数量
const int n_x=7,n_y=7,n_z=7;

// 设定随机引入的粒子数
const int particles=64;

// This function returns a random double between 0 and 1
double rnd() {return double(rand())/RAND_MAX;}

int main() {
	int i=0;
	double x,y,z;

	// Create a container with the geometry given above, and make it
	// non-periodic in each of the three coordinates. Allocate space for 8
	// particles within each computational block.
	container con(x_min,x_max,y_min,y_max,z_min,z_max,n_x,n_y,n_z,
			false,false,false,8);

	// Add four plane walls to the container to make a tetrahedron
	wall_plane p1(1,1,1,1);con.add_wall(p1);
	wall_plane p2(-1,-1,1,1);con.add_wall(p2);
	wall_plane p3(1,-1,-1,1);con.add_wall(p3);
	wall_plane p4(-1,1,-1,1);con.add_wall(p4);

	//随机将粒子插入容器中，检查它们是否在四面体内
	while(i<particles) {
		x=x_min+rnd()*(x_max-x_min);
		y=y_min+rnd()*(y_max-y_min);
		z=z_min+rnd()*(z_max-z_min);
		if (con.point_inside(x,y,z)) {
			con.put(i,x,y,z);i++;
		}
	}

	// Output the particle positions and the Voronoi cells in Gnuplot and
	// POV-Ray formats
	//splot 'E:\\voro++\\random_points\\random_points\\tetrahedron_p.gnu' with points, 'E:\\voro++\\random_points\\random_points\\tetrahedron_v.gnu' with lines

	con.draw_particles("E:\\voro++\\random_points\\random_points\\tetrahedron_p.gnu");
	con.draw_cells_gnuplot("E:\\voro++\\random_points\\random_points\\tetrahedron_v.gnu");
	con.draw_particles_pov("E:\\voro++\\random_points\\random_points\\tetrahedron_p.pov");
	con.draw_cells_pov("E:\\voro++\\random_points\\random_points\\tetrahedron_v.pov");
}
