static void     get_o_c(t_cylinder *cyl, float o_c[3)
{
    o_c[0] = -cyl->coords[0];
    o_c[1] = -cyl->coords[1];
    o_c[2] = -cyl->coords[2];
}

static int		intersection(t_cylinder *cyl, float ray[3], float **p, float **n)
{
	float eq[3];
	float o_c[3];
	float disc;
	float t[3];

    get_o_c(cyl, o_c);
	eq[0] = dot(ray, ray) - pow(dot(ray, cyl->vector), 2);
	eq[1] = (dot(ray, o_c) - dot(ray, cyl->vector) * dot(o_c, cyl->vector)) * 2;
	eq[2] = dot(o_c, o_c) - pow(dot(o_c, cyl->vector), 2) - pow(cyl->diameter / 2, 2);
	disc = eq[1] * eq[1] - 4 * eq[0] * eq[2];
	if (disc < 0)
		return (0);
	t[1] = (-eq[1] - sqrt(disc)) / (2 * eq[0]);
	t[2] = (-eq[1] + sqrt(disc)) / (2 * eq[0]);
	if (check_borders(cyl, t[1], ray, o_c) == 1)
		t[0] = t[1];
	else if (check_borders(cyl, t[2], ray, o_c) == 1)
		t[0] = t[2];
	else
		return (0);
	*p = get_point(ray, t[0]);
	*n = get_normal(*p, cyl->coords);
	return (1);
}