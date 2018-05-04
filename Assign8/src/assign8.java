import java.util.*;
import java.io.*;
import java.lang.*;

public class assign8 {
	public static int conversion_time(char[] time) // Assume time == "aa:bb"
	{
		int Time;
		char[] hour = new char[2];
		char[] min = new char[2];
		for(int i = 0; i < 2; i++)
			hour[i] = time[i];
		for(int i = 0; i < 2; i++)
			min[i] = time[i + 3];
		
		String Minute = String.valueOf(min);
		String Hour = String.valueOf(hour);
		
		Time = Integer.parseInt(Hour) * 60 + Integer.parseInt(Minute);
		
		return Time;
	}
	public static void represent_longer_schedule(int day, int clocks, int interval)
	{
		int hour_ = clocks / 60;
		int min_ = clocks % 60;

		int hour = interval / 60;
		int min = interval % 60;

		System.out.printf("Day #" + day + ": the longest nap starts at " + hour_ + ":");
		if (min_ == 0)
			System.out.printf("00");
		else
			System.out.print(min_);
		
		if (hour == 0)
			System.out.println(" and will last for " + min + " minutes.");
		else
			System.out.println(" and will last for " + hour + " hours and " + min + " minutes.");
	}
	public static void selection_sort_algorithm(int[] arr)
	{
		for (int i = 0; i < arr.length; i++)
		{
			int min = arr[i];
			int pos = i;

			for (int j = i; j < arr.length; j++)
			{
				if (min > arr[j])
				{
					min = arr[j];
					pos = j;
				}
			}
			arr[pos] = arr[i];
			arr[i] = min;
		}
	}
	public static void main(String[] args) throws ArrayIndexOutOfBoundsException, IOException{
		Scanner inFile = new Scanner(new File("input.txt"));
		while(inFile.hasNext()){
			int Test_Case = inFile.nextInt();
			String dummy = inFile.nextLine();
			int[] first = new int[Test_Case];
			int[] last = new int[Test_Case];
			int day = 1;
			
			for(int i = 0; i < Test_Case; i++)
			{
				String str = inFile.nextLine();
				char[] first_time = new char[5];
				char[] last_time = new char[5];

				for(int j = 0; j < 5; j++)
					first_time[j] = str.toCharArray()[j];
				for(int j = 0; j < 5; j++)
					last_time[j] = str.toCharArray()[j + 6];
				
				first[i] = conversion_time(first_time);
				last[i] = conversion_time(last_time);
			} // input clear!
			
			selection_sort_algorithm(first);
			selection_sort_algorithm(last);

			int max = first[0] - 10 * 60;
			int clock = 10 * 60;

			for (int i = 0; i < Test_Case - 1; i++)
			{
				int interval = first[i + 1] - last[i];
				if (max < interval)
				{
					max = interval;
					clock = last[i];
				}
			}
			if (max < 18 * 60 - last[Test_Case - 1])
			{
				max = 18 * 60 - last[Test_Case - 1];
				clock = last[Test_Case - 1];
			}
			represent_longer_schedule(day, clock, max);

			day++;
		}
		inFile.close();
	}
}
