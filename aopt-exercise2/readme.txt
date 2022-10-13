1. Use RandomNumberGenerator::get random nd vector(n) to generate two n-dimensional random vectors x, y resambling 2 random points
2. for loop n_eval-1 times to compare the convex condition, if fail return false to break the loop, if after max_sampling_times all pass, return true
3. changed the return false line after TODO part because this way the code looks cleaner, otherwise I have to use goto to jump from inside loop to the return sentence.
