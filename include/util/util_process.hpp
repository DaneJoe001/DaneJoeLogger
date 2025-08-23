#pragma once

/**
 * @namespace DaneJoe
 * @brief DaneJoe命名空间
  */
namespace DaneJoe
{
    /**
     * @class UtilProcess
     * @brief 进程工具类
     */
    class UtilProcess
    {
    public:
        /**
         * @brief 获取进程ID
         * @return 进程ID
         */
        static int get_pid();
    };
};