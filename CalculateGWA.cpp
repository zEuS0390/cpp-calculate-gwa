#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

// Struct to represent grades with final and reexam marks
struct Grade {
	float _final {0};   // Final grade
	float reexam {0};   // Reexamination grade
};

// Class to represent a course record
class Record {
public:
	std::string course_code;    // Course code (e.g., CPE 101)
	std::string desc_title;     // Course description/title (e.g., Introduction to Computer Engineering)
	Grade grade;                // Grade information (final and reexam grades)
	int credits;                // Number of credit hours for the course

	// Constructor to initialize a Record object with course data
	Record(const std::string& course_code,
 	       const std::string& desc_title,
	       const Grade& grade,
	       int credits):
	       course_code(course_code),    // Initialize course code
	       desc_title(desc_title),      // Initialize course title
	       grade(grade),                // Initialize grade
	       credits(credits) {}          // Initialize credits
};

// Overloading the << operator to output a Record object in a readable format
std::ostream& operator<<(std::ostream& os, const Record& record) {
	os << record.course_code << ", ";           // Output course code
	os << record.desc_title << ", ";            // Output course title
	os << record.grade._final << ", ";          // Output final grade
	os << record.credits;                       // Output credits
	return os;                                  // Return the output stream for chaining
}

// Function to calculate General Weighted Average (GWA) for a list of courses
std::vector<float> calculateGWA(std::vector<Record>& semester_grades) {
	if (semester_grades.empty()) return {};     // If no courses, return an empty vector

	float total_quality_points = 0, total_credit_hours = 0, gwa;    // Variables to store total quality points and total credits
	for (const Record& record: semester_grades) {
		// Calculate total quality points based on the final or reexam grade, whichever is non-zero, and weighted by credits
		total_quality_points += ((record.grade.reexam == 0)? record.grade._final : record.grade.reexam) * record.credits;
		total_credit_hours += record.credits;   // Sum up total credits
	}
	gwa = total_quality_points / total_credit_hours;            // Calculate GWA

	return {total_quality_points, total_credit_hours, gwa};     // Return results as a vector
}

// Main function
int main(void) {

	// Transcript of Records with course codes, descriptions, grades, and credits
	std::vector<Record> grades = {
		{"CPE 101", "Introduction to Computer Engineering", {1.5, 0}, 3},
		{"CPE 201", "Digital Logic Design", {1.0, 0}, 4},
		{"CPE 301", "Computer Architecture", {1.2, 0}, 3},
		{"CPE 401", "Operating Systems", {1.1, 0}, 3},
		{"CPE 501", "Algorithm Design", {1.0, 0}, 4},
		{"CPE 601", "Database Systems", {1.5, 0}, 3},
		{"CPE 701", "Computer Networks", {1.2, 0}, 3},
		{"CPE 801", "Software Engineering", {1.4, 0}, 4},
		{"CPE 901", "Machine Learning", {1.3, 0}, 3},
		{"CPE 1001", "Embedded Systems", {1.1, 0}, 3}
	};

	// Calculate the GWA for the courses in grades
	std::vector<float> result = calculateGWA(grades);

	// If result is not empty, print the calculated values
	if (!result.empty()) {
		std::cout << std::fixed << std::setprecision(2)                     // Set fixed point notation with 2 decimal places
			  << "Number of Courses: " << grades.size() << "\n"             // Print number of courses
			  << "Total Quality Points: " << result[0] << "\n"              // Print total quality points
			  << "Total Credit Hours: " << result[1] << "\n"                // Print total credit hours
			  << "General Weighted Average (GWA): " << result[2] << "\n";   // Print calculated GWA
	}

	return 0;  // Return 0 to indicate successful execution
}
