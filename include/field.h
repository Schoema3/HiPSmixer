#include "cell.h"

class Fields {

	class Scalar_Cell: public Cell {
		double value;

		public:
			Scalar_Cell(double input_value){ value = input_value; }
			inline double getValue(){ return value; }
			inline void   setValue(input_value){ value = input_value; }
	};

	class Vector_Cell: public Cell {
		double valueX;
		double valueY;
		double valueZ;

		public:
			Vector_Cell(
				double input_valueX,
				double input_valueY,
				double input_valueZ){ 

				valueX = input_valueX;
				valueY = input_valueY;
				valueZ = input_valueZ;
			}
			// to be done
	};

	class Field_Cell: public Cell {

		//This should be templated?
		Scalar_Cell exampleScalar;
		Vector_Cell exampleVector;

		public:
			Field_Cell();
			
			int getVTKType();	
			std::vector<int> getPoints();

			bool isPointInside(
				std::vector<double> pointA,
				std::vector<double> pointB
			);
	};


	std::string< fieldNames> name;

	std::vector< Cell* > field;

	public:

		Field(std::vector< Cell* >* input_mesh, std::string name, double initial_value);

		void updateField(int index, double value);

		std::vector<double> toVTK();

		inline std::string getName(){ return name; }

		inline std::vector< Cell* >* exportField(){ return &field; }	
};

