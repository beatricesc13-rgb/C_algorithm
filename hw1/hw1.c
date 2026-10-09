#include <limits.h>
#include <stdio.h>

static int is_leap_year(int year)
{
	return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

static int days_in_month(int year, int month)
{
	static const int days[] = { 31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31 };
	if (month == 2 && is_leap_year(year))
		return 29;
	return days[month - 1];
}

static int is_valid_date(int year, int month, int day)
{
	return year >= 1 && month >= 1 && month <= 12
		&& day >= 1 && day <= days_in_month(year, month);
}

static int get_weekday(int year, int month, int day)
{
	if (month < 3) {
		month += 12;
		year--;
	}
	return (day + (13 * (month + 1)) / 5 + year + year / 4
		- year / 100 + year / 400) % 7;
}

static long long days_before_year(long long year)
{
	long long previous_year = year - 1;
	return previous_year * 365 + previous_year / 4
		- previous_year / 100 + previous_year / 400;
}

static long long date_to_ordinal(int year, int month, int day)
{
	long long ordinal = days_before_year(year);
	for (int current_month = 1; current_month < month; current_month++)
		ordinal += days_in_month(year, current_month);
	return ordinal + day - 1;
}

static void ordinal_to_date(long long ordinal, long long *year,
		int *month, int *day)
{
	long long low = 1;
	long long high = ordinal / 365 + 2;
	while (low + 1 < high) {
		long long middle = low + (high - low) / 2;
		if (days_before_year(middle) <= ordinal)
			low = middle;
		else
			high = middle;
	}

	*year = low;
	long long day_of_year = ordinal - days_before_year(low);
	*month = 1;
	while (day_of_year >= days_in_month((int)low, *month)) {
		day_of_year -= days_in_month((int)low, *month);
		(*month)++;
	}
	*day = (int)day_of_year + 1;
}

int main(void)
{
	int year, month, day;
	int end_year, end_month, end_day;
	long long extra_days;
	char input[100];
	const char *weekdays[] = {
		"Saturday", "Sunday", "Monday", "Tuesday",
		"Wednesday", "Thursday", "Friday"
	};
	const char *months[] = {
		"January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December"
	};

	printf("請輸入 yyyy/mm/dd、yyyy/mm/dd - yyyy/mm/dd 或 yyyy/mm/dd + x：");
	if (fgets(input, sizeof(input), stdin) == NULL) {
		printf("日期格式錯誤。\n");
		return 1;
	}

	if (sscanf(input, "%d/%d/%d - %d/%d/%d",
		&year, &month, &day, &end_year, &end_month, &end_day) == 6) {
		if (!is_valid_date(year, month, day)
			|| !is_valid_date(end_year, end_month, end_day)) {
			printf("日期格式錯誤。\n");
			return 1;
		}
		long long difference = date_to_ordinal(end_year, end_month, end_day)
			- date_to_ordinal(year, month, day);
		if (difference < 0) {
			printf("結束日期不能小於開始日期。\n");
			return 1;
		}
		printf("%lld days from %s %d,%d to %s %d,%d\n",
			difference, months[month - 1], day, year,
			months[end_month - 1], end_day, end_year);
		return 0;
	}

	if (sscanf(input, "%d/%d/%d + %lld",
		&year, &month, &day, &extra_days) == 4) {
		if (!is_valid_date(year, month, day) || extra_days < 0) {
			printf("日期或天數格式錯誤。\n");
			return 1;
		}
		long long ordinal = date_to_ordinal(year, month, day);
		if (extra_days > LLONG_MAX - ordinal) {
			printf("日期超出可計算範圍。\n");
			return 1;
		}
		long long end_year;
		int end_month, end_day;
		ordinal_to_date(ordinal + extra_days, &end_year, &end_month, &end_day);
		printf("%lld days after %s %d,%d is %s %d,%lld\n",
			extra_days, months[month - 1], day, year,
			months[end_month - 1], end_day, end_year);
		return 0;
	}

	if (sscanf(input, "%d/%d/%d", &year, &month, &day) == 3) {
		if (!is_valid_date(year, month, day)) {
			printf("日期格式錯誤。\n");
			return 1;
		}
		printf("%s %d,%d is %s\n", months[month - 1], day, year,
			weekdays[get_weekday(year, month, day)]);
		return 0;
	}

	printf("日期格式錯誤。\n");
	return 1;
}