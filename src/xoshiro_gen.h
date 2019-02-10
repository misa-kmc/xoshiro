#ifndef MISA_KMC_XOSHIRO_H
#define MISA_KMC_XOSHIRO_H


#include <limits>
#include <numeric>
#include <algorithm>
#include <ctime>
#include "xoshiro.h"

// copied from https://github.com/atframework/atframe_utils/blob/master/include/random/random_generator.h
namespace util {
    namespace random {
        /**
         * 随机数包装类，用以提供高级功能
         */
        template<typename CoreType>
        class random_manager_wrapper {
        public:
            typedef CoreType core_type;
            typedef typename core_type::result_type result_type;

        private:
            core_type core_;

        public:
            random_manager_wrapper() {}

            random_manager_wrapper(result_type rd_seed) : core_(rd_seed) {}

            inline core_type &get_core() { return core_; }

            inline const core_type &get_core() const { return core_; }

            /**
             * 初始化随机数种子
             * @param [in] rd_seed 随机数种子
             */
            void init_seed(result_type rd_seed) { core_.init_seed(rd_seed); }

            /**
             * 初始化随机数种子
             * @note 取值范围为 [first, last)
             * @param [in] first 随机数种子散列值起始位置
             * @param [in] last 随机数种子散列值结束位置
             */
            template<typename It>
            void init_seed(It &first, It last) {
                core_.init_seed(first, last);
            }

            /**
             * 产生一个随机数
             * @return 产生的随机数
             */
            result_type random() { return core_(); }

            /**
             * 产生一个随机数
             * @return 产生的随机数
             */
            result_type operator()() { return random(); }

            /**
             * 产生一个随机数
             * @param [in] lowest 下限
             * @param [in] highest 上限(必须大于lowest)
             * @note 取值范围 [lowest, highest)
             * @return 产生的随机数
             */
            template<typename ResaultType>
            ResaultType random_between(ResaultType lowest, ResaultType highest) {
                if (highest <= lowest) {
                    return lowest;
                }
                result_type res = (*this)();
                return static_cast<ResaultType>(res % static_cast<result_type>(highest - lowest)) + lowest;
            }

        public:
            // ------------ Support for UniformRandomBitGenerator ------------
            static inline constexpr result_type min()

            noexcept { return std::numeric_limits<result_type>::min(); }

            static inline constexpr result_type max()

            noexcept { return std::numeric_limits<result_type>::max(); }

            inline result_type g() noexcept { return random(); }

            // ------------ Support for RandomFunc ------------
            /**
             * 产生一个随机数
             * @return 产生的随机数
             */
            inline result_type operator()(result_type mod)

            noexcept {
                if (0 == mod) {
                    return random();
                } else {
                    return random() % mod;
                }
            }

            template<typename RandomIt>
            void shuffle(RandomIt first, RandomIt last) {
#if defined(__cplusplus) && __cplusplus >= 201103L
                std::shuffle(first, last, std::move(*this));
#elif defined(_MSVC_LANG) && _MSVC_LANG >= 201402L
                std::shuffle(first, last, std::move(*this));
#else
                std::random_shuffle(first, last, *this);
#endif
            }
        };

        // @see http://xoshiro.di.unimi.it
        // 循环节： 2^128 − 1
        typedef random_manager_wrapper<core::xoshinro_engine_128<false> > xoroshiro128_starstar;
        // 循环节： 2^128 − 1，少一次旋转，更快一点点
        typedef random_manager_wrapper<core::xoshinro_engine_128<true> > xoroshiro128_plus;
        // 循环节： 2^256 − 1
        typedef random_manager_wrapper<core::xoshinro_engine_256<false> > xoshiro256_starstar;
        // 循环节： 2^256 − 1，少一次旋转，更快一点点
        typedef random_manager_wrapper<core::xoshinro_engine_256<true> > xoshiro256_plus;
    } // namespace random
} // namespace util

#endif //MISA_KMC_XOSHIRO_H
