#pragma once
#include <iostream>

	class Log
	{
	public:
		static void Init();

		static Log* GetLogger() { return s_Logger; }
		static void SetSeparator(char separator) { GetLogger()->m_Separator = separator; }

		template <typename... Types>
		void Info(Types... objects)
		{
			SetColor(2);
			PrintTime();
			Print(objects...);
			SetColor(7);
		}
		template <typename... Types>
		void Trace(Types... objects)
		{
			SetColor(7);
			PrintTime();
			Print(objects...);
		}
		template <typename... Types>
		void Err(Types... objects)
		{
			SetColor(12);
			PrintTime();
			Print(objects...);
			SetColor(7);
		}
		template <typename... Types>
		void State(Types... objects)
		{
			SetColor(6);
			PrintTime();
			Print(objects...);
			SetColor(7);
		}

	private:
		template <typename T>
		void Print(const T& obj)
		{
			std::cout << obj << std::endl;
		}
		template <typename T, typename... Types>
		void Print(const T& obj, const Types&... objects)
		{
			std::cout << obj << m_Separator;
			Print(objects...);
		}
		void SetColor(int color);
		void PrintTime();
	private:
		static Log* s_Logger;
		void* m_ConsoleHandle;
		char m_Separator;
	};


#define LOG_INFO(...) Log::GetLogger()->Info(__VA_ARGS__)
#define LOG_TRACE(...) Log::GetLogger()->Trace(__VA_ARGS__)
#define LOG_ERROR(...) Log::GetLogger()->Err(__VA_ARGS__)
#define LOG_STATE(...) Log::GetLogger()->State(__VA_ARGS__)
#define LOG_ASSERT(b, ...)  if (!(b)) { Log::GetLogger()->Err(__VA_ARGS__); __debugbreak();}

