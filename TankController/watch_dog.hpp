#pragma once

namespace util
{

class watch_dog
{
    private:
    bool _is_error_occured_in_previous_execution;
	
	//100ms応答がなければリセットがかかる
	static const unsigned char _clock_source = 0x0F;	//内部クロック Φ/8192
	static const unsigned char _write_value = 0x0C;		//定期的な処理でWDレジスタに書き込まれる値
    
    public:
    watch_dog();
    bool is_error_occured_in_previous_execution() const { return _is_error_occured_in_previous_execution; }
    void watch();
    void run();
    void stop();
};

}