#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <memory>
/*懒汉模式:按照需求创建实例 线程不安全 */
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
	//进行两次判断 减少上锁次数
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
	std::cout << "地址是: " << this << std::endl;
}

SingleClass::SingleClass() {
	std::cout << "构造函数" << std::endl;
}

SingleClass::~SingleClass()
{
	std::cout << "析构函数" << std::endl;
}

/*懒汉模式:内部静态变量的实现*/
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
	SingleInstance() { std::cout << "构造函数" << std::endl; }
	~SingleInstance() { std::cout << "析构函数" << std::endl; }
};

/*饿汉模式*/
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
		std::cout << "singleclass:构造函数" << std::endl;
	}
	~singleclass() {
		std::cout << "singleclass:析构函数" << std::endl;
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