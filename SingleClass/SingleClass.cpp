#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <memory>
/*����ģʽ:�������󴴽�ʵ�� �̲߳���ȫ */
class SingleClass {
public:
	static SingleClass* get_singleclass();
	static void delete_singleclass();
	void print();
private:
	SingleClass();
	~SingleClass();
	SingleClass(const SingleClass&) = delete;
	const SingleClass& operator= (const SingleClass&) = delete;

private:
	static SingleClass* single_class;
	static std::mutex mtx_;
};

SingleClass* SingleClass::single_class = nullptr;
std::mutex SingleClass::mtx_;

SingleClass* SingleClass::get_singleclass()
{
	//���������ж� ������������
	if (single_class == nullptr) {
		std::unique_lock<std::mutex> lock(mtx_);
		if (single_class == nullptr) {
			single_class = new SingleClass();
			return single_class;
		}
	}
}

void SingleClass::delete_singleclass()
{
	if (single_class) {
		delete single_class;
		single_class = nullptr;
	}
}

void SingleClass::print()
{
	std::cout << "��ַ��: " << this << std::endl;
}

SingleClass::SingleClass() {
	std::cout << "���캯��" << std::endl;
}

SingleClass::~SingleClass()
{
	std::cout << "��������" << std::endl;
}

/*����ģʽ:�ڲ���̬������ʵ��*/
class SingleInstance {
public:
	static SingleInstance& get_instance() {
		static SingleInstance instance;
		return instance;
	}
	void print() { std::cout << "hello" << std::endl; }
private:
	SingleInstance(const SingleInstance&) = delete;
	const SingleInstance& operator= (const SingleClass&) = delete;
	SingleInstance() { std::cout << "���캯��" << std::endl; }
	~SingleInstance() { std::cout << "��������" << std::endl; }
};

/*����ģʽ*/
class singleclass {
public:
	static singleclass* get_instance() {
		return ptr_;
	}
	static void delete_instance() {
		if (ptr_) {
			delete ptr_;
			ptr_ = nullptr;
		}
	}
	void print() {
		std::cout << "singleclass--print()" << std::endl;
	}
	
	
private:
	static singleclass* ptr_;
	singleclass() {
		std::cout << "singleclass:���캯��" << std::endl;
	}
	~singleclass() {
		std::cout << "singleclass:��������" << std::endl;
	}
	
};

singleclass* singleclass::ptr_ = new(singleclass);

int main() {
	SingleClass::get_singleclass()->print();
	SingleClass::get_singleclass()->delete_singleclass();
	SingleInstance::get_instance().print();

	singleclass::get_instance()->print();
	return 0;
}