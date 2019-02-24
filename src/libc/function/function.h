/**
 * @file function.h
 * @author Keeton Feavel and James Osborne
 * @brief Defines a "function" that allows us
 * to suppress unused variable errors
 * @version 0.1
 * @date 2019-02-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef FUNCTION_H
#define FUNCTION_H

/* Sometimes we want to keep parameters to a function for later use
 * and this is a solution to avoid the 'unused parameter' compiler warning */
#define UNUSED(x) (void)(x)

#endif /* FUNCTION_H */