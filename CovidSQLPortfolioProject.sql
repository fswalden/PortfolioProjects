Select *
From CovidPortfolioDB..CovidDeaths
order by 3,4

--Select *
--From CovidPortfolioDB..CovidVaccinations
--order by 3,4

--Select Data to use:

Select Location, date, total_cases, new_cases, total_deaths, population
From CovidPortfolioDB..CovidDeaths
order by 1,2

--Total cases vs total deaths

Select Location, date, total_cases, total_deaths, (total_deaths / total_cases) * 100 as DeathPercentage
From CovidPortfolioDB..CovidDeaths
Where location like '%states%' --optional line, to show death rate in US
order by 1,2

-- Total Cases vs Population

Select Location, date, total_cases, population, (total_cases/population) * 100 as CasePercentage
From CovidPortfolioDB..CovidDeaths
order by 1,2

--Countries with Highest Infection Rate 

Select Location, population, MAX(total_cases) as HighestInfectionCount, MAX((total_cases/population) * 100) as CasePercentage
From CovidPortfolioDB..CovidDeaths
Group by Location, population
order by CasePercentage desc

--Countries with highest death count
Select Location, MAX(cast(total_deaths as int)) as TotalDeathCount
From CovidPortfolioDB..CovidDeaths
Where continent is not null
Group by Location
order by TotalDeathCount desc

--Continents with highest death count
Select location, MAX(cast(total_deaths as int)) as TotalDeathCount
From CovidPortfolioDB..CovidDeaths
Where continent is null
Group by location
order by TotalDeathCount desc


--Global
Select SUM(new_cases) as total_cases, SUM(cast(new_deaths as int)) as total_deaths, SUM(cast(new_deaths as int))/SUM(new_cases) * 100 as DeathPercentage
From CovidPortfolioDB..CovidDeaths
Where continent is not null
order by 1,2

-- Population vs vaccinations
Select dea.continent, dea.location, dea.date, dea.population, vac.new_vaccinations,
SUM(CONVERT(int, vac.new_vaccinations)) OVER (Partition by dea.location Order by dea.location, dea.date) as RollingPeopleVaccinated
From CovidPortfolioDB..CovidDeaths dea
Join CovidPortfolioDB..CovidVaccinations vac
	On dea.location = vac.location 
	and dea.date = vac.date
where dea.continent is not null
order by 2, 3

-- Calculation using CTE

With PopvsVac (Continent, Location, Date, Population, New_Vaccinations, RollingPeopleVaccinated)
as
(
Select dea.continent, dea.location, dea.date, dea.population, vac.new_vaccinations
, SUM(CONVERT(int,vac.new_vaccinations)) OVER (Partition by dea.Location Order by dea.location, dea.Date) as RollingPeopleVaccinated
--, (RollingPeopleVaccinated/population)*100
From CovidPortfolioDB..CovidDeaths dea
Join CovidPortfolioDB..CovidVaccinations vac
	On dea.location = vac.location
	and dea.date = vac.date
where dea.continent is not null 
--order by 2,3
)
Select *, (RollingPeopleVaccinated/Population)*100
From PopvsVac

-- Calculation using temp table

DROP Table if exists #PercentPopulationVaccinated
Create Table #PercentPopulationVaccinated
(
Continent nvarchar(255),
Location nvarchar(255),
Date datetime,
Population numeric,
New_vaccinations numeric,
RollingPeopleVaccinated numeric
)

Insert into #PercentPopulationVaccinated
Select dea.continent, dea.location, dea.date, dea.population, vac.new_vaccinations
, SUM(CONVERT(int,vac.new_vaccinations)) OVER (Partition by dea.Location Order by dea.location, dea.Date) as RollingPeopleVaccinated
--, (RollingPeopleVaccinated/population)*100
From CovidPortfolioDB..CovidDeaths dea
Join CovidPortfolioDB..CovidVaccinations vac
	On dea.location = vac.location
	and dea.date = vac.date
--where dea.continent is not null 
--order by 2,3

Select *, (RollingPeopleVaccinated/Population)*100
From #PercentPopulationVaccinated


-- Creating View

Create View VacPercentage as
Select dea.continent, dea.location, dea.date, dea.population, vac.new_vaccinations
, SUM(CONVERT(int,vac.new_vaccinations)) OVER (Partition by dea.Location Order by dea.location, dea.Date) as RollingPeopleVaccinated
--, (RollingPeopleVaccinated/population)*100
From CovidPortfolioDB..CovidDeaths dea
Join CovidPortfolioDB..CovidVaccinations vac
	On dea.location = vac.location
	and dea.date = vac.date
where dea.continent is not null 