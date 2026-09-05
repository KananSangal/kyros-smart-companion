/** @type {import('tailwindcss').Config} */
export default {
  content: ['./index.html', './src/**/*.{js,jsx}'],
  theme: {
    extend: {
      colors: {
        onyx: {
          950: '#05070a',
          900: '#090c11',
          850: '#0d1118',
          800: '#12161f',
          750: '#171c28',
          700: '#1d2432',
          600: '#252e3f',
          500: '#33405a',
          400: '#46566f',
          300: '#5f7090',
        },
        kyros: {
          orange: '#f97316',
          amber: '#fb923c',
          saffron: '#ea580c',
          deep: '#7c2d12',
          cream: '#fff7ed',
          sand: '#ffedd5',
          leaf: '#16a34a',
          green: '#22c55e',
          moss: '#14532d',
          ink: '#e7e5e4', // inverted for dark surfaces
        },
      },
      fontFamily: {
        display: ['"Segoe UI"', 'ui-rounded', 'system-ui', 'sans-serif'],
        led: ['"Courier New"', 'ui-monospace', 'SFMono-Regular', 'Menlo', 'monospace'],
      },
      boxShadow: {
        press:
          '0 0 0 1px rgba(0,0,0,.4), 0 1px 0 rgba(255,255,255,.06) inset, 0 2px 8px rgba(0,0,0,.6)',
        'press-active':
          '0 0 0 1px rgba(0,0,0,.5), 0 1px 0 rgba(255,255,255,.03) inset, 0 0 14px rgba(249,115,22,.45)',
        'glow-orange': '0 0 18px -2px rgba(249,115,22,.55)',
        'glow-green': '0 0 18px -2px rgba(34,197,94,.5)',
      },
      keyframes: {
        bob: {
          '0%,100%': { transform: 'translateY(0) rotate(-1deg)' },
          '50%': { transform: 'translateY(-10px) rotate(1.5deg)' },
        },
        wiggle: {
          '0%,100%': { transform: 'rotate(-3deg)' },
          '50%': { transform: 'rotate(3deg)' },
        },
      },
      animation: {
        bob: 'bob 0.9s ease-in-out infinite',
        wiggle: 'wiggle 0.5s ease-in-out infinite',
      },
    },
  },
  plugins: [],
};
