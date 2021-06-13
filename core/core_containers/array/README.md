# Dynamic Array

A multi-purpose dynamic array implementation for the C language.

A dynamic array is an array which grows automatically without the need to
explicitly reallocate and copy data over. This implementation provieds
functionality to create and manipulate a dynamic array in an efficient
manner. This implementation emulates the functionality of a C++ std::vector.

## Design

-   Dynamic resizing. Doubles the size of the array when maximum size
    is reached.
-   Datatype agnostic. When creating the array user specifies an element size
    for the array (preferrably using the sizeof operator).
-   Data is kept straight in memory for fast iteration. This is not a pointer
    array, all the data is in the array itself avoiding fragmentation.
-   Provides get and add methods, but also let's user typecast the arrays data
    portion and iterate it directly for maximum performance.
-   Alrady allocated memory can be assigned to the array without copying. Array
    will use the allocated memory and manipulate it directly unless it runs out.

## Typedefs

```c

typedef struct  s_array
{
    t_byte     *data;
    t_size      len;
    t_size      alloc_size;
    t_size      elem_size;
}               t_array;

```

`len` refers to the number of rawbers in the array. `alloc_size` is the amount
of allocated space for `elem_size` sized objects. These values should never be
manipulated by the user but they can be accessed and checked easily.

## Functions

These are general descriptions about the functions in the library and their
intended usage. For a detailed description refer to the source-code file
of each function.

### General

```c
t_array         arr(t_size elem_size);
t_ssize         arr_alloc(t_array *src, t_size alloc_size);
t_ssize         arr_free(t_array *src);
t_ssize         arr_grow(t_array *src, t_size newsize);
t_ssize         arr_null(t_array *arr);
```

`arr` is the only function that creates a new array. After usage that array has
to be freed using arr_free. If the user wants to grow the size of the array
manually, `arr_grow` can be used. Normally resizing is handled internally though so
arr_grow should only be used in special cases. In case of an error a null array
might be assigned. To check if an array is null, function `arr_null` can be used.

### Manipulating the Elements

```c
t_ssize         arr_assign(t_array *dst, void *data, t_size len);
t_ssize         arr_add(t_array *src, void *node, t_size index);
t_ssize         arr_add_first(t_array *src, void *node);
t_ssize         arr_add_last(t_array *src, void *node);
t_ssize         arr_add_mult(t_array *src, t_size count, ...);
t_ssize         arr_put(t_array *dst, void *src, t_size size);
t_ssize         arr_del(t_array *src, t_size index);
t_ssize         arr_del_first(t_array *src);
t_ssize         arr_del_last(t_array *src);
void            *arr_get(t_array *src, t_size index);
void            *arr_get_first(t_array *src);
void            *arr_get_last(t_array *src);
void            *arr_take(void *dst, t_array *src, t_size index);
void            *arr_take_first(void *dst, t_array *src);
void            *arr_take_last(void *dst, t_array *src);
```

This group of functions is used to manipulate elements in the array. Find
differs from search such that find matches one element whereas search matches
all elements in the array `key`. Get means getting a pointer to an element,
whereas take gets the element and deletes it (called pop in some
implementations).

### Manipulating the Array

```c

t_ssize         arr_find(t_array *src, void *key);
t_ssize         arr_search(t_array *src, t_array *key);
t_ssize         arr_copy(t_array *dst, t_array *src);
t_ssize         arr_join(t_array *dst, t_array *src);
t_ssize         arr_join_mult(t_array *dst, t_size count, ...);
t_ssize         arr_rotate(t_array *arr, t_ssize steps);
t_ssize         arr_iter(t_array *src,
                t_ssize (*f)(void *, t_size));
t_ssize         arr_iter_range(t_array *src, t_size start, t_size end,
                t_ssize (*f)(void *, t_size));
t_ssize         arr_parse(t_array *dst, t_array *src,
                t_ssize (*f)(t_array *, void *));

```

This group of functions is used to manipulte or iterate the array in various
ways.

-------------------------------------------------------------------------------
