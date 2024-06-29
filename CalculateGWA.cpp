#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

struct Grade {
	float _final {0};
	float reexam {0};
};

class Record {
public:
	std::string course_code;
	std::string desc_title;
	Grade grade;
	int credits;

	Record(const std::string& course_code, 
 	       const std::string& desc_title, 
	       const Grade& grade, 
	       int credits):
	       course_code(course_code), 
	       desc_title(desc_title),
	       grade(grade), 
	       credits(credits) {}
};

std::ostream& operator<<(std::ostream& os, const Record& record) {
	os << record.course_code << ", ";
	os << record.desc_title << ", ";
	os << record.grade._final << ", ";
	os << record.credits;
	return os;
}

std::vector<float> calculateGWA(std::vector<Record>& semester_grades) {
	if (semester_grades.empty()) return {};

	float total_quality_points = 0, total_credit_hours = 0, gwa;
	for (const Record& record: semester_grades) {
		total_quality_points += ((record.grade.reexam == 0)? record.grade._final : record.grade.reexam) * record.credits;
		total_credit_hours += record.credits;
	}
	gwa = total_quality_points / total_credit_hours;

	return {total_quality_points, total_credit_hours, gwa};
}

// Main function
int main(void) {

	// Transcript of Records
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

	std::vector<float> result = calculateGWA(grades);

	if (!result.empty()) {
		std::cout << std::fixed << std::setprecision(2)
			  << "Number of Courses: " << grades.size() << "\n"
			  << "Total Quality Points: " << result[0] << "\n"
			  << "Total Credit Hours: " << result[1] << "\n"
			  << "General Weighted Average (GWA): " << result[2] << "\n";
	}

	return 0;
}
