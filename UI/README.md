# mkulima-bora

Hero icons is actually a lighter and better package than react icons (25x smaller).

## CSS GRID

- It all starts with a grid container.
- Any direct child element is considered as a grid item.
- We have total control over the grid items are located ie how many rows and columns they can occupy , where they should start and end.
- When configuring position , the count starts with one instead of zero for both rows and columns.
- If you do not specify where they are located, they will automatically be placed in the next available cell.
- To specify where they are positions , use the tailwindcss prop `grid-col-start-1 grid-col-end-3 grid-row-start-1 grid-row-end-3`
- To specify how many rows and columns they should occupy , use the tailwindcss prop `col-span-2 row-span-2`
- And basically we are done !

## CHART.JS

- We just need to understand the data structure that chart.js expects which is quite straight forward.
- We need to pass in an object with a labels property (Represent the global x - axis labels) and a datasets property (Contains dataset label which is used as a key to know which line / color is which)
- Additional customization to the chart can be done as per the documentation eg adding a title , changing the color of the line etc.
- Here are some of the resources that helped :-
  - ![Chart_JS Youtube Channel](https://www.youtube.com/@ChartJS-tutorials)
  - ![Chart_JS Documentation](https://www.chartjs.org/docs/latest/)
