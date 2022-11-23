#ifndef UTCI_H
#define UTCI_H

double calc_utci(double temp_air, double temp_rad, double humidity,
		double wind_spd)
{
	double t_a = temp_air;
	double d_t_r = temp_rad - temp_air;
	double pa = humidity / 10.0; /* humidity is in ehPa */
	double v = wind_spd;

	return (t_a + (6.07562052E-01) + (-2.27712343E-02) * t_a
			+ (8.06470249E-04) * t_a * t_a
			+ (-1.54271372E-04) * t_a * t_a * t_a
			+ (-3.24651735E-06) * t_a * t_a * t_a * t_a
			+ (7.32602852E-08) * t_a * t_a * t_a * t_a * t_a
			+ (1.35959073E-09) * t_a * t_a * t_a * t_a * t_a * t_a
			+ (-2.25836520) * v + (8.80326035E-02) * t_a * v
			+ (2.16844454E-03) * t_a * t_a * v
			+ (-1.53347087E-05) * t_a * t_a * t_a * v
			+ (-5.72983704E-07) * t_a * t_a * t_a * t_a * v
			+ (-2.55090145E-09) * t_a * t_a * t_a * t_a * t_a * v
			+ (-7.51269505E-01) * v * v
			+ (-4.08350271E-03) * t_a * v * v
			+ (-5.21670675E-05) * t_a * t_a * v * v
			+ (1.94544667E-06) * t_a * t_a * t_a * v * v
			+ (1.14099531E-08) * t_a * t_a * t_a * t_a * v * v
			+ (1.58137256E-01) * v * v * v
			+ (-6.57263143E-05) * t_a * v * v * v
			+ (2.22697524E-07) * t_a * t_a * v * v * v
			+ (-4.16117031E-08) * t_a * t_a * t_a * v * v * v
			+ (-1.27762753E-02) * v * v * v * v
			+ (9.66891875E-06) * t_a * v * v * v * v
			+ (2.52785852E-09) * t_a * t_a * v * v * v * v
			+ (4.56306672E-04) * v * v * v * v * v
			+ (-1.74202546E-07) * t_a * v * v * v * v * v
			+ (-5.91491269E-06) * v * v * v * v * v * v
			+ (3.98374029E-01) * d_t_r
			+ (1.83945314E-04) * t_a * d_t_r
			+ (-1.73754510E-04) * t_a * t_a * d_t_r
			+ (-7.60781159E-07) * t_a * t_a * t_a * d_t_r
			+ (3.77830287E-08) * t_a * t_a * t_a * t_a * d_t_r
			+ (5.43079673E-10) * t_a * t_a * t_a * t_a * t_a * d_t_r
			+ (-2.00518269E-02) * v * d_t_r
			+ (8.92859837E-04) * t_a * v * d_t_r
			+ (3.45433048E-06) * t_a * t_a * v * d_t_r
			+ (-3.77925774E-07) * t_a * t_a * t_a * v * d_t_r
			+ (-1.69699377E-09) * t_a * t_a * t_a * t_a * v * d_t_r
			+ (1.69992415E-04) * v * v * d_t_r
			+ (-4.99204314E-05) * t_a * v * v * d_t_r
			+ (2.47417178E-07) * t_a * t_a * v * v * d_t_r
			+ (1.07596466E-08) * t_a * t_a * t_a * v * v * d_t_r
			+ (8.49242932E-05) * v * v * v * d_t_r
			+ (1.35191328E-06) * t_a * v * v * v * d_t_r
			+ (-6.21531254E-09) * t_a * t_a * v * v * v * d_t_r
			+ (-4.99410301E-06) * v * v * v * v * d_t_r
			+ (-1.89489258E-08) * t_a * v * v * v * v * d_t_r
			+ (8.15300114E-08) * v * v * v * v * v * d_t_r
			+ (7.55043090E-04) * d_t_r * d_t_r
			+ (-5.65095215E-05) * t_a * d_t_r * d_t_r
			+ (-4.52166564E-07) * t_a * t_a * d_t_r * d_t_r
			+ (2.46688878E-08) * t_a * t_a * t_a * d_t_r * d_t_r
			+ (2.42674348E-10) * t_a * t_a * t_a * t_a * d_t_r
					* d_t_r
			+ (1.54547250E-04) * v * d_t_r * d_t_r
			+ (5.24110970E-06) * t_a * v * d_t_r * d_t_r
			+ (-8.75874982E-08) * t_a * t_a * v * d_t_r * d_t_r
			+ (-1.50743064E-09) * t_a * t_a * t_a * v * d_t_r
					* d_t_r
			+ (-1.56236307E-05) * v * v * d_t_r * d_t_r
			+ (-1.33895614E-07) * t_a * v * v * d_t_r * d_t_r
			+ (2.49709824E-09) * t_a * t_a * v * v * d_t_r * d_t_r
			+ (6.51711721E-07) * v * v * v * d_t_r * d_t_r
			+ (1.94960053E-09) * t_a * v * v * v * d_t_r * d_t_r
			+ (-1.00361113E-08) * v * v * v * v * d_t_r * d_t_r
			+ (-1.21206673E-05) * d_t_r * d_t_r * d_t_r
			+ (-2.18203660E-07) * t_a * d_t_r * d_t_r * d_t_r
			+ (7.51269482E-09) * t_a * t_a * d_t_r * d_t_r * d_t_r
			+ (9.79063848E-11) * t_a * t_a * t_a * d_t_r * d_t_r
					* d_t_r
			+ (1.25006734E-06) * v * d_t_r * d_t_r * d_t_r
			+ (-1.81584736E-09) * t_a * v * d_t_r * d_t_r * d_t_r
			+ (-3.52197671E-10) * t_a * t_a * v * d_t_r * d_t_r
					* d_t_r
			+ (-3.36514630E-08) * v * v * d_t_r * d_t_r * d_t_r
			+ (1.35908359E-10) * t_a * v * v * d_t_r * d_t_r * d_t_r
			+ (4.17032620E-10) * v * v * v * d_t_r * d_t_r * d_t_r
			+ (-1.30369025E-09) * d_t_r * d_t_r * d_t_r * d_t_r
			+ (4.13908461E-10) * t_a * d_t_r * d_t_r * d_t_r * d_t_r
			+ (9.22652254E-12) * t_a * t_a * d_t_r * d_t_r * d_t_r
					* d_t_r
			+ (-5.08220384E-09) * v * d_t_r * d_t_r * d_t_r * d_t_r
			+ (-2.24730961E-11) * t_a * v * d_t_r * d_t_r * d_t_r
					* d_t_r
			+ (1.17139133E-10) * v * v * d_t_r * d_t_r * d_t_r
					* d_t_r
			+ (6.62154879E-10) * d_t_r * d_t_r * d_t_r * d_t_r
					* d_t_r
			+ (4.03863260E-13) * t_a * d_t_r * d_t_r * d_t_r * d_t_r
					* d_t_r
			+ (1.95087203E-12) * v * d_t_r * d_t_r * d_t_r * d_t_r
					* d_t_r
			+ (-4.73602469E-12) * d_t_r * d_t_r * d_t_r * d_t_r
					* d_t_r * d_t_r + (5.12733497) * pa
			+ (-3.12788561E-01) * t_a * pa
			+ (-1.96701861E-02) * t_a * t_a * pa
			+ (9.99690870E-04) * t_a * t_a * t_a * pa
			+ (9.51738512E-06) * t_a * t_a * t_a * t_a * pa
			+ (-4.66426341E-07) * t_a * t_a * t_a * t_a * t_a * pa
			+ (5.48050612E-01) * v * pa
			+ (-3.30552823E-03) * t_a * v * pa
			+ (-1.64119440E-03) * t_a * t_a * v * pa
			+ (-5.16670694E-06) * t_a * t_a * t_a * v * pa
			+ (9.52692432E-07) * t_a * t_a * t_a * t_a * v * pa
			+ (-4.29223622E-02) * v * v * pa
			+ (5.00845667E-03) * t_a * v * v * pa
			+ (1.00601257E-06) * t_a * t_a * v * v * pa
			+ (-1.81748644E-06) * t_a * t_a * t_a * v * v * pa
			+ (-1.25813502E-03) * v * v * v * pa
			+ (-1.79330391E-04) * t_a * v * v * v * pa
			+ (2.34994441E-06) * t_a * t_a * v * v * v * pa
			+ (1.29735808E-04) * v * v * v * v * pa
			+ (1.29064870E-06) * t_a * v * v * v * v * pa
			+ (-2.28558686E-06) * v * v * v * v * v * pa
			+ (-3.69476348E-02) * d_t_r * pa
			+ (1.62325322E-03) * t_a * d_t_r * pa
			+ (-3.14279680E-05) * t_a * t_a * d_t_r * pa
			+ (2.59835559E-06) * t_a * t_a * t_a * d_t_r * pa
			+ (-4.77136523E-08) * t_a * t_a * t_a * t_a * d_t_r * pa
			+ (8.64203390E-03) * v * d_t_r * pa
			+ (-6.87405181E-04) * t_a * v * d_t_r * pa
			+ (-9.13863872E-06) * t_a * t_a * v * d_t_r * pa
			+ (5.15916806E-07) * t_a * t_a * t_a * v * d_t_r * pa
			+ (-3.59217476E-05) * v * v * d_t_r * pa
			+ (3.28696511E-05) * t_a * v * v * d_t_r * pa
			+ (-7.10542454E-07) * t_a * t_a * v * v * d_t_r * pa
			+ (-1.24382300E-05) * v * v * v * d_t_r * pa
			+ (-7.38584400E-09) * t_a * v * v * v * d_t_r * pa
			+ (2.20609296E-07) * v * v * v * v * d_t_r * pa
			+ (-7.32469180E-04) * d_t_r * d_t_r * pa
			+ (-1.87381964E-05) * t_a * d_t_r * d_t_r * pa
			+ (4.80925239E-06) * t_a * t_a * d_t_r * d_t_r * pa
			+ (-8.75492040E-08) * t_a * t_a * t_a * d_t_r * d_t_r
					* pa
			+ (2.77862930E-05) * v * d_t_r * d_t_r * pa
			+ (-5.06004592E-06) * t_a * v * d_t_r * d_t_r * pa
			+ (1.14325367E-07) * t_a * t_a * v * d_t_r * d_t_r * pa
			+ (2.53016723E-06) * v * v * d_t_r * d_t_r * pa
			+ (-1.72857035E-08) * t_a * v * v * d_t_r * d_t_r * pa
			+ (-3.95079398E-08) * v * v * v * d_t_r * d_t_r * pa
			+ (-3.59413173E-07) * d_t_r * d_t_r * d_t_r * pa
			+ (7.04388046E-07) * t_a * d_t_r * d_t_r * d_t_r * pa
			+ (-1.89309167E-08) * t_a * t_a * d_t_r * d_t_r * d_t_r
					* pa
			+ (-4.79768731E-07) * v * d_t_r * d_t_r * d_t_r * pa
			+ (7.96079978E-09) * t_a * v * d_t_r * d_t_r * d_t_r
					* pa
			+ (1.62897058E-09) * v * v * d_t_r * d_t_r * d_t_r * pa
			+ (3.94367674E-08) * d_t_r * d_t_r * d_t_r * d_t_r * pa
			+ (-1.18566247E-09) * t_a * d_t_r * d_t_r * d_t_r
					* d_t_r * pa
			+ (3.34678041E-10) * v * d_t_r * d_t_r * d_t_r * d_t_r
					* pa
			+ (-1.15606447E-10) * d_t_r * d_t_r * d_t_r * d_t_r
					* d_t_r * pa + (-2.8062640600) * pa * pa
			+ (5.48712484E-01) * t_a * pa * pa
			+ (-3.99428410E-03) * t_a * t_a * pa * pa
			+ (-9.54009191E-04) * t_a * t_a * t_a * pa * pa
			+ (1.93090978E-05) * t_a * t_a * t_a * t_a * pa * pa
			+ (-3.08806365E-01) * v * pa * pa
			+ (1.16952364E-02) * t_a * v * pa * pa
			+ (4.95271903E-04) * t_a * t_a * v * pa * pa
			+ (-1.90710882E-05) * t_a * t_a * t_a * v * pa * pa
			+ (2.10787756E-03) * v * v * pa * pa
			+ (-6.98445738E-04) * t_a * v * v * pa * pa
			+ (2.30109073E-05) * t_a * t_a * v * v * pa * pa
			+ (4.17856590E-04) * v * v * v * pa * pa
			+ (-1.27043871E-05) * t_a * v * v * v * pa * pa
			+ (-3.04620472E-06) * v * v * v * v * pa * pa
			+ (5.14507424E-02) * d_t_r * pa * pa
			+ (-4.32510997E-03) * t_a * d_t_r * pa * pa
			+ (8.99281156E-05) * t_a * t_a * d_t_r * pa * pa
			+ (-7.14663943E-07) * t_a * t_a * t_a * d_t_r * pa * pa
			+ (-2.66016305E-04) * v * d_t_r * pa * pa
			+ (2.63789586E-04) * t_a * v * d_t_r * pa * pa
			+ (-7.01199003E-06) * t_a * t_a * v * d_t_r * pa * pa
			+ (-1.06823306E-04) * v * v * d_t_r * pa * pa
			+ (3.61341136E-06) * t_a * v * v * d_t_r * pa * pa
			+ (2.29748967E-07) * v * v * v * d_t_r * pa * pa
			+ (3.04788893E-04) * d_t_r * d_t_r * pa * pa
			+ (-6.42070836E-05) * t_a * d_t_r * d_t_r * pa * pa
			+ (1.16257971E-06) * t_a * t_a * d_t_r * d_t_r * pa * pa
			+ (7.68023384E-06) * v * d_t_r * d_t_r * pa * pa
			+ (-5.47446896E-07) * t_a * v * d_t_r * d_t_r * pa * pa
			+ (-3.59937910E-08) * v * v * d_t_r * d_t_r * pa * pa
			+ (-4.36497725E-06) * d_t_r * d_t_r * d_t_r * pa * pa
			+ (1.68737969E-07) * t_a * d_t_r * d_t_r * d_t_r * pa
					* pa
			+ (2.67489271E-08) * v * d_t_r * d_t_r * d_t_r * pa * pa
			+ (3.23926897E-09) * d_t_r * d_t_r * d_t_r * d_t_r * pa
					* pa + (-3.53874123E-02) * pa * pa * pa
			+ (-2.21201190E-01) * t_a * pa * pa * pa
			+ (1.55126038E-02) * t_a * t_a * pa * pa * pa
			+ (-2.63917279E-04) * t_a * t_a * t_a * pa * pa * pa
			+ (4.53433455E-02) * v * pa * pa * pa
			+ (-4.32943862E-03) * t_a * v * pa * pa * pa
			+ (1.45389826E-04) * t_a * t_a * v * pa * pa * pa
			+ (2.17508610E-04) * v * v * pa * pa * pa
			+ (-6.66724702E-05) * t_a * v * v * pa * pa * pa
			+ (3.33217140E-05) * v * v * v * pa * pa * pa
			+ (-2.26921615E-03) * d_t_r * pa * pa * pa
			+ (3.80261982E-04) * t_a * d_t_r * pa * pa * pa
			+ (-5.45314314E-09) * t_a * t_a * d_t_r * pa * pa * pa
			+ (-7.96355448E-04) * v * d_t_r * pa * pa * pa
			+ (2.53458034E-05) * t_a * v * d_t_r * pa * pa * pa
			+ (-6.31223658E-06) * v * v * d_t_r * pa * pa * pa
			+ (3.02122035E-04) * d_t_r * d_t_r * pa * pa * pa
			+ (-4.77403547E-06) * t_a * d_t_r * d_t_r * pa * pa * pa
			+ (1.73825715E-06) * v * d_t_r * d_t_r * pa * pa * pa
			+ (-4.09087898E-07) * d_t_r * d_t_r * d_t_r * pa * pa
					* pa
			+ (6.14155345E-01) * pa * pa * pa * pa
			+ (-6.16755931E-02) * t_a * pa * pa * pa * pa
			+ (1.33374846E-03) * t_a * t_a * pa * pa * pa * pa
			+ (3.55375387E-03) * v * pa * pa * pa * pa
			+ (-5.13027851E-04) * t_a * v * pa * pa * pa * pa
			+ (1.02449757E-04) * v * v * pa * pa * pa * pa
			+ (-1.48526421E-03) * d_t_r * pa * pa * pa * pa
			+ (-4.11469183E-05) * t_a * d_t_r * pa * pa * pa * pa
			+ (-6.80434415E-06) * v * d_t_r * pa * pa * pa * pa
			+ (-9.77675906E-06) * d_t_r * d_t_r * pa * pa * pa * pa
			+ (8.82773108E-02) * pa * pa * pa * pa * pa
			+ (-3.01859306E-03) * t_a * pa * pa * pa * pa * pa
			+ (1.04452989E-03) * v * pa * pa * pa * pa * pa
			+ (2.47090539E-04) * d_t_r * pa * pa * pa * pa * pa
			+ (1.48348065E-03) * pa * pa * pa * pa * pa * pa);
} /* End function calc_utci */


#endif
